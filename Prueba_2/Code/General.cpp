#include"General.h"

std::string FindLoadFilePath(const char* filter)
{
    OPENFILENAME filetoLoad;
    char size[260] = {};
    char size2[260] = {};
    std::string aux;
    ZeroMemory(&filetoLoad, sizeof(OPENFILENAME));
    filetoLoad.lStructSize = sizeof(OPENFILENAME);
    filetoLoad.hwndOwner = GetActiveWindow();
    filetoLoad.lpstrFile = (LPWSTR)(size);
    filetoLoad.nMaxFile = sizeof(filetoLoad);
    //filetoLoad.lpstrFilter = filter;
    filetoLoad.nFilterIndex = 1;
    filetoLoad.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileName(&filetoLoad))
    {
        int counter = 0;
        int b = 0;
        for (int a = 0; a < 260; a++) {


            if (counter == 1 && size[a] == '\0') {
                break;
            }
            else if (size[a] == '\0') {
                counter++;
            }
            else {

                size2[b] = size[a];


                counter = 0;
                b++;
            }
        }
        aux = size2;
        return aux;
    }
    //return filetoLoad.lpstrFile;

    return std::string("Error at Loading Scene");

}

std::string FindSaveFilePath(const char* filter)
{
    size_t sizee = strlen(filter) + 1;
    wchar_t* portName = new wchar_t[sizee];

    size_t outSize;
    mbstowcs_s(&outSize, portName, sizee, filter, sizee - 1);

    LPCWSTR ptr = portName;
    char size2[260] = {};
    char size[260] = {};
    OPENFILENAME fileToSave;
    ZeroMemory(&fileToSave, sizeof(OPENFILENAME));
    fileToSave.lStructSize = sizeof(OPENFILENAME);
    fileToSave.hwndOwner = GetActiveWindow();
    fileToSave.lpstrFile =(LPWSTR) size;
    fileToSave.nMaxFile = sizeof(fileToSave);
    fileToSave.lpstrFilter = ptr;
    fileToSave.nFilterIndex = 1;
    fileToSave.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR| OFN_NOTESTFILECREATE;
    std::string aux;
    if (GetSaveFileName(&fileToSave)) {


        int counter = 0;
        int b = 0;
        for (int a = 0; a < 260; a++) {


            if (counter == 1 && size[a] == '\0') {
                break;
            }
            else if (size[a] == '\0') {
                counter++;
            }
            else {
                if (size[a] == '\\') {
                    size2[b] = '/';
                }
                else {
                    size2[b] = size[a];

                }              
                counter = 0;
                b++;
            }
        }
        aux = size2;
        return aux;
    }
        

    return std::string("Error at Saving Scene");
}

bool SaveFile(const char* path,const char* mode, void* dataBuffer, float size)
{
    FILE* fp;

    fopen_s(&fp, path, mode);
     
    if (fwrite(dataBuffer, 1, size, fp) != size) {
        return false;
    }

    fclose(fp);
    return true;
}
bool ReadFile(const char* path, const char* mode, void* dataBuffer, float size,int startMode, int start) {
    FILE* fp;
    fopen_s(&fp, path, mode);
    fseek(fp,start , startMode);
    fread(dataBuffer, 1, size, fp);
    fclose(fp);
    return true;
}
bool OpenFile(const char* path, const char* mode, FILE** file) {

    fopen_s(file, path, mode);
    return true;
}
bool CloseFile(FILE* file) {
    fclose(file);
    return true;
}
bool ReadOpenedFile(FILE* file, void* dataBuffer, float size, int startMode, int start) {
    fseek(file, start, startMode);
    fread(dataBuffer, 1, size, file);
    return true;
}
bool WriteOpenedFile(FILE* file, void* dataBuffer, float size, int startMode, int start) {
    fseek(file, start, startMode);
    fwrite(dataBuffer, 1, size, file);
    return true;
}
