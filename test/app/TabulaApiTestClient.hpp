//
// Created by kuimov on 04.08.23.
//

#ifndef TABULA_TABULAAPITESTCLIENT_HPP
#define TABULA_TABULAAPITESTCLIENT_HPP

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiClient)

/**
 * Test API Client
 * Use this client to call application APIs.
 */
class TabulaApiTestClient : public oatpp::web::client::ApiClient {
    API_CLIENT_INIT(TabulaApiTestClient)

    API_CALL("GET", "/board", getBoard);
};

#include OATPP_CODEGEN_END(ApiClient)

#endif //TABULA_TABULAAPITESTCLIENT_HPP
