//
// Created by kuimov on 04.08.23.
//

#ifndef TABULA_TESTCOMPONENT_HPP
#define TABULA_TESTCOMPONENT_HPP

#include "db/TabulaColumnsClient.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "oatpp/network/virtual_/client/ConnectionProvider.hpp"
#include "oatpp/network/virtual_/server/ConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/macro/component.hpp"
#include "AppComponent.hpp"

/**
 * Test Components config
 */
class TestComponent {
public:

    /**
     * Config Component
     */
    OATPP_CREATE_COMPONENT(oatpp::Object<ConfigDto>, config)([this] {
        const char* configPath = CONFIG_PATH;
        auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

        oatpp::String configText = oatpp::String::loadFromFile(configPath);
        if (configText) {
            auto profiles = objectMapper->readFromString<oatpp::Fields<oatpp::Object<ConfigDto>>>(configText);

            OATPP_LOGD("Server", "Loading configuration profile test");

            auto profile = profiles.getValueByKey("test", nullptr);
            if (!profile) {
                throw std::runtime_error("No configuration profile found. Server won't run.");
            }
            return profile;
        }

        OATPP_LOGE("AppComponent", "Can't load configuration file at path %s", configPath);
        throw std::runtime_error("[AppComponent]: Can't load configuration file");
    } ());

    /**
     * Create oatpp virtual network interface for test networking
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, virtualInterface) ([] {
        return oatpp::network::virtual_::Interface::obtainShared("virtualhost");
    } ());

    /**
     * Create server ConnectionProvider of oatpp virtual connections for test
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider) ([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface);
        return oatpp::network::virtual_::server::ConnectionProvider::createShared(interface);
    } ());

    /**
     * Create client ConnectionProvider of oatpp virtual connections for test
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider) ([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface);
        return oatpp::network::virtual_::client::ConnectionProvider::createShared(interface);
    } ());

    /**
     * Create Router Component
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter) ([] {
        return oatpp::web::server::HttpRouter::createShared();
    } ());

    /**
     * Create ConnectionHandler component which uses Router component to route requests
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler) ([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    } ());

    /**
     * Create ObjectMapper component to serialize/deserialize DTOs in Controller's API
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper) ([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    } ());

    /**
     * Create DbClient component.
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<TabulaColumnsDbClient>, tabulaColumnsDbClient) ([] {
        OATPP_COMPONENT(oatpp::Object<ConfigDto>, config);
        auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(
                config->dbConnectionString);
        auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
                                                                              10,
                                                                              std::chrono::seconds(5));
        auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);
        return std::make_shared<TabulaColumnsDbClient>(executor);
    }());
};

#endif //TABULA_TESTCOMPONENT_HPP
