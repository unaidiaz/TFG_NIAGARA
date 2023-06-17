#ifndef GENERAL_H
#define GENERAL_H
#define WIDTH 1200
#define HEIGHT 900
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include<shlobj_core.h>
#include<string>
std::string FindLoadFilePath(const char* filter);
std::string FindSaveFilePath(const char* filter);
bool SaveFile(const char* path, const char* mode, void* dataBuffer, float size);
bool ReadFile(const char* path, const char* mode, void* dataBuffer, float size, int startMode = 0, int start = 0);
bool OpenFile(const char* path, const char* mode,FILE** file);
bool CloseFile(FILE* file);
bool ReadOpenedFile(FILE* file, void* dataBuffer, float size, int startMode = 0, int start = 0);
bool WriteOpenedFile(FILE* file,void* dataBuffer, float size, int startMode = 0, int start = 0);

#endif
