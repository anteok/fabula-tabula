//
// Created by kuimov on 03.08.23.
//

#ifndef TABULA_DTOS_HPP
#define TABULA_DTOS_HPP

#include <ctime>
#include <oatpp/core/Types.hpp>
#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"


/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Board Data-Transfer object
 */
class BoardColumnsDTO : public oatpp::DTO {

    DTO_INIT(BoardColumnsDTO, DTO);

    DTO_FIELD(Int32, statusCode);   // Status code field
    DTO_FIELD(String, message);     // Message field
};

#include OATPP_CODEGEN_END(DTO)

#endif //TABULA_DTOS_HPP
