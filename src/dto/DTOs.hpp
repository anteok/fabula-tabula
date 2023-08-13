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
class BoardColumnDTO : public oatpp::DTO {

    DTO_INIT(BoardColumnDTO, DTO);

    DTO_FIELD(String, id);
    DTO_FIELD(String, name);
    DTO_FIELD(Boolean, active);
    DTO_FIELD(Int16, order_num);
};

class BoardColumnsListDTO: public  oatpp::DTO  {

    DTO_INIT(BoardColumnsListDTO, DTO);

    DTO_FIELD(Vector<Object<BoardColumnDTO>>, columns);
};

#include OATPP_CODEGEN_END(DTO)

#endif //TABULA_DTOS_HPP
