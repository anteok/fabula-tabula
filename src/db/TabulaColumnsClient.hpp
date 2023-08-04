//
// Created by kuimov on 04.08.23.
//

#ifndef TABULA_TABULACOLUMNSCLIENT_HPP
#define TABULA_TABULACOLUMNSCLIENT_HPP

#include "oatpp/orm/DbClient.hpp"

#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class TabulaColumnsDbClient : public oatpp::orm::DbClient {
public:

    TabulaColumnsDbClient(const std::shared_ptr<oatpp::orm::Executor>& executor) : oatpp::orm::DbClient(executor) {}

    QUERY(getColumns,
        "SELECT * FROM TabulaColumns;")
};

#include OATPP_CODEGEN_END(DbClient)

#endif //TABULA_TABULACOLUMNSCLIENT_HPP
