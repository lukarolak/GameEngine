#include <FileIO/FileIO.h>
#include <fstream>
#include <Debuging/Assert.h>
std::vector<char> FileIO::ReadFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    ENG_ASSERT(file.is_open() != false, "failed to open file!");

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}
