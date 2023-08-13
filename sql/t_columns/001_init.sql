CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TABLE IF NOT EXISTS TabulaColumns (
    id              varchar (64) PRIMARY KEY,
    name            varchar (256) NOT NULL,
    active          boolean NOT NULL DEFAULT true,
    order_num       integer NOT NULL,
    CONSTRAINT      UK_TABULACOLUMNS_NAME UNIQUE (name)
);

INSERT INTO
    TabulaColumns (id, name, active, order_num)
VALUES
    (uuid_generate_v4(), 'BACKLOG', true, 0),
    (uuid_generate_v4(), 'IN_DEV', true, 0),
    (uuid_generate_v4(), 'IN_REVIEW', true, 0),
    (uuid_generate_v4(), 'IN_TEST', true, 0),
    (uuid_generate_v4(), 'DONE', true, 0);
