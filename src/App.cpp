//
// Created by kuimov on 03.08.23.
//
#include "AppComponent.hpp"
#include "controller/BoardController.hpp"

#include "oatpp/network/Server.hpp"


void run() {

    AppComponent components;
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

    auto boardController = std::make_shared<BoardController>();
    router->addController(boardController);

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    oatpp::network::Server server(connectionProvider, connectionHandler);

    OATPP_LOGI("Tabula app", "Server running on port %s", connectionProvider->getProperty("port").getData());

    server.run();
}

int main(int argc, const char * argv[]) {
    oatpp::base::Environment::init();
    run();
    oatpp::base::Environment::destroy();
    return 0;
}