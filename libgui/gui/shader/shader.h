#ifndef GUI_SHADER_H
#define GUI_SHADER_H

#include "../libdearimgui/dearimgui/glad/glad.h" 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <filesystem>

class Shader
{
public:

Shader()
{
     bIsLoaded = false;
}

Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    load(vertexShaderSource,fragmentShaderSource);
}

~Shader()
{

}

public:
    void load(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
    {
        shaderProgramID = glCreateProgram();
        unsigned vertexShader   = compileShader(GL_VERTEX_SHADER,vertexShaderSource);
        unsigned fragmentShader = compileShader(GL_FRAGMENT_SHADER,fragmentShaderSource);
        
        /// Attach shader buffer to shader program
        glAttachShader(shaderProgramID, vertexShader);
        glAttachShader(shaderProgramID, fragmentShader);
        /// Link all contained shader
        glLinkProgram(shaderProgramID);
        // Check for linking errors
        int  successCode;
        glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &successCode);
        if (!successCode) {
            /// Get log length, and create a char array of length
            int length;
            glGetShaderiv(shaderProgramID,GL_INFO_LOG_LENGTH, &length);
            char* message = (char*) alloca(length*sizeof(char)); /// alloc on stack
            glGetProgramInfoLog(shaderProgramID, length, NULL, message);
            std::cout << "Failed to link the shader\n" << message << std::endl;
            glDeleteProgram(shaderProgramID);
            return;
        }
        // Cleaning up shader
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Set flag on
        bIsLoaded = true;
    }

    void loadFile(const std::string& vertexShaderStringPath, const std::string& fragmentShaderStringPath)
    {
        /// Read vertex Shader
        std::filesystem::path vertexShaderPath(vertexShaderStringPath);
        std::ifstream vertexShaderFile(vertexShaderPath, std::ios::in | std::ios::binary); // open in binary mode
        if (!vertexShaderFile) 
        {
            throw std::ios_base::failure("Failed to open file: " + vertexShaderPath.string());
        }
        std::ostringstream vertexShaderContent;
        vertexShaderContent << vertexShaderFile.rdbuf(); // read the whole file

        /// Read fragment Shader
        std::filesystem::path fragmentShaderPath(fragmentShaderStringPath);
        std::ifstream fragmentShaderFile(vertexShaderPath, std::ios::in | std::ios::binary); // open in binary mode
        if (!fragmentShaderFile) 
        {
            throw std::ios_base::failure("Failed to open file: " + fragmentShaderPath.string());
        }
        std::ostringstream fragmentShaderContent;
        fragmentShaderContent << fragmentShaderFile.rdbuf(); // read the whole file

        /// load the shader
        load(vertexShaderContent.str(),fragmentShaderContent.str());
    }

public:
    void use()
    {
        if(!bIsLoaded)
        {
            std::cout << "Error: Shader not loaded" << std::endl;
            return;
        }
        glUseProgram(shaderProgramID);
    }

public:

    void set1Bool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value); 
    }

    void set1Int(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value); 
    }

    void set1Float(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value); 
    }

    void set2Int(const std::string &name, int value1, int value2) const
    { 
        glUniform2i(glGetUniformLocation(shaderProgramID, name.c_str()), value1, value2); 
    }

    void set2Float(const std::string &name, float value1, float value2) const
    { 
        glUniform2f(glGetUniformLocation(shaderProgramID, name.c_str()), value1, value2); 
    }

    void set3Int(const std::string &name, int value1, int value2, int value3) const
    { 
        glUniform3i(glGetUniformLocation(shaderProgramID, name.c_str()), value1, value2, value3); 
    }

    void set3Float(const std::string &name, float value1, float value2, float value3) const
    { 
        glUniform3f(glGetUniformLocation(shaderProgramID, name.c_str()), value1, value2, value3); 
    }

    void set4Int(const std::string &name, int value1, int value2, int value3, int value4) const
    { 
        glUniform4i(glGetUniformLocation(shaderProgramID, name.c_str()), value1, value2, value3, value4); 
    }

    void set4Float(const std::string &name, float value1, float value2, float value3, float value4) const
    { 
        glUniform4f(glGetUniformLocation(shaderProgramID, name.c_str()), value1, value2, value3, value4); 
    }


private:
    unsigned compileShader(unsigned shaderType, const std::string& shaderSource)
    {
        unsigned shaderID = glCreateShader(shaderType);       /// Create shader
        const char* shaderCharSource = shaderSource.c_str(); 
        glShaderSource(shaderID, 1, &shaderCharSource, NULL); /// Load shader source code, assuming NULL as termination
        glCompileShader(shaderID);                            /// Compile shader
        /// Check shader compilation
        int  successCode;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &successCode);
        /// Check success code
        if(!successCode)
        {
            /// Get log length, and create a char array of length
            int length;
            glGetShaderiv(shaderID,GL_INFO_LOG_LENGTH, &length);
            char* message = (char*) alloca(length*sizeof(char)); /// alloc on stack
            glGetShaderInfoLog(shaderID, length, NULL, message);
            std::cout << "Failed to compile shader \n" << message << std::endl;
            glDeleteShader(shaderID);
            return 0;
        }
        return shaderID;
    }



private:

    bool     bIsLoaded;       // Flag to load the shader
    unsigned shaderProgramID; // ID of the shader program


};

#endif // GUI_SHADER_H