#include "shader.h"

using namespace std;

GLuint vertex_shader, fragment_shader;
GLuint shader_program;

shader::shader() {
}

void shader::create(const char* vertex_path, const char* fragment_path) {

    string vertex_code, fragment_code;
    ifstream vshader_file, fshader_file;

    vshader_file.exceptions(ifstream::failbit | ifstream::badbit);
    fshader_file.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        vshader_file.open(vertex_path);
        fshader_file.open(fragment_path);
        stringstream vshader_stream, fshader_stream;

        vshader_stream << vshader_file.rdbuf();
        fshader_stream << fshader_file.rdbuf();

        vshader_file.close();
        fshader_file.close();

        vertex_code = vshader_stream.str();
        fragment_code = fshader_stream.str();
    }
    catch(ifstream::failure& error) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << error.what() << endl;
    }

    const char* vshader_code = vertex_code.c_str();
    const char* fshader_code = fragment_code.c_str();

    // Vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vshader_code, NULL);
    glCompileShader(vertex_shader);

    error("VERTEX");

    // Fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fshader_code, NULL);
    glCompileShader(fragment_shader);

    error("FRAGMENT");

    // link shaders
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    error("PROGRAM");
}

void shader::use() {
    glUseProgram(shader_program);
}

void shader::destroy() {
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void shader::destroy_program() {
    glDeleteProgram(shader_program);
}

void shader::error(string type) {
    int success;
    char infoLog[1024];

    if (type == "PROGRAM") {
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
            cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
            exit(-1);
        }
    }
    else {
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
            cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << endl;
            exit(-1);
        }
    }
}

void shader::set_bool(const string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(shader_program, name.c_str()), (int)value);
}

void shader::set_int(const string& name, int value) const
{
    glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value);
}

void shader::set_float(const string& name, float value) const
{
    glUniform1f(glGetUniformLocation(shader_program, name.c_str()), value);
}

void shader::set_vec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(shader_program, name.c_str()), 1, &value[0]);
}
void shader::_set_vec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(shader_program, name.c_str()), x, y);
}

void shader::set_vec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(shader_program, name.c_str()), 1, &value[0]);
}
void shader::_set_vec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(shader_program, name.c_str()), x, y, z);
}

void shader::set_vec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(shader_program, name.c_str()), 1, &value[0]);
}
void shader::_set_vec4(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(shader_program, name.c_str()), x, y, z, w);
}

void shader::set_mat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void shader::set_mat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void shader::set_mat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}