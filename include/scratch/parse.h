#include "./project/project.h"

/**
 * @brief 
 * 
 * @param[in] file_path Path to the desired .sb3 file
 * @param[out] identifier Identifier to later parse the project
 * 
 * @return bool Whether the project successfully loaded
 */
bool scratch_project_load(const char* file_path, size_t* identifier);