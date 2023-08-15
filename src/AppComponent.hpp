//
// Created by kuimov on 03.08.23.
//

#ifndef TABULA_APPCOMPONENT_HPP
#define TABULA_APPCOMPONENT_HPP

#include "db/TabulaColumnsClient.hpp"
#include "dto/configDto.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp-postgresql/orm.hpp"

#include "oatpp/core/macro/component.hpp"


/**
 * Class which creates and holds Application components and registers components in oatpp::base::Environment
 * Order of components initialization is from top to bottom
 */
class AppComponent {
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

            const char *profileArg = std::getenv("CONFIG_PROFILE");
            if (profileArg == nullptr) {
                profileArg = "dev";
            }

            OATPP_LOGD("Server", "Loading configuration profile '%s'", profileArg);

            auto profile = profiles.getValueByKey(profileArg, nullptr);
            if (!profile) {
                throw std::runtime_error("No configuration profile found. Server won't run.");
            }
            return profile;
        }

        OATPP_LOGE("AppComponent", "Can't load configuration file at path %s", configPath);
        throw std::runtime_error("[AppComponent]: Can't load configuration file");
    } ());

    /**
     * Create ConnectionProvider component which listens on the port
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider) ([] {
        OATPP_COMPONENT(oatpp::Object<ConfigDto>, config);
        return oatpp::network::tcp::server::ConnectionProvider::createShared({
            config->host,
            config->port,
            oatpp::network::Address::IP_4
        });
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

#endif //TABULA_APPCOMPONENT_HPP
