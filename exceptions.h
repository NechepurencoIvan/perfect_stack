#pragma once

struct outOfMemoryException {
    outOfMemoryException(char* ex) {
        description = ex;
    }
    char* description;
};

struct emptyStackTrasactionException {
    emptyStackTrasactionException(char* ex) {
        description = ex;
    }
    char* description;
};
