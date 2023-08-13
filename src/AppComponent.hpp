//
// Created by kuimov on 03.08.23.
//

#ifndef TABULA_APPCOMPONENT_HPP
#define TABULA_APPCOMPONENT_HPP

#include "db/TabulaColumnsClient.hpp"
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
     * Create ConnectionProvider component which listens on the port
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider) ([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4});
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
        auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(
                "postgresql://admin:pass@127.0.0.1:5432/tabula");
        auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
                                                                              10,
                                                                              std::chrono::seconds(5));
        auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);
        return std::make_shared<TabulaColumnsDbClient>(executor, true);
    }());

};

#endif //TABULA_APPCOMPONENT_HPP
