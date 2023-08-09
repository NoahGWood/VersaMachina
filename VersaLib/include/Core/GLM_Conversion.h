#pragma once
#include "Core/Base.h"
#include <string>
#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>

namespace YAML
{
    template <>
    struct convert<glm::mat4>
    {
        static Node encode(const glm::mat4& rhs)
        {
            Node node;
            node.push_back(rhs[0][0]);
            node.push_back(rhs[0][1]);
            node.push_back(rhs[0][2]);
            node.push_back(rhs[0][3]);
            node.push_back(rhs[1][0]);
            node.push_back(rhs[1][1]);
            node.push_back(rhs[1][2]);
            node.push_back(rhs[1][3]);
            node.push_back(rhs[2][0]);
            node.push_back(rhs[2][1]);
            node.push_back(rhs[2][2]);
            node.push_back(rhs[2][3]);
            node.push_back(rhs[3][0]);
            node.push_back(rhs[3][1]);
            node.push_back(rhs[3][2]);
            node.push_back(rhs[3][3]);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, glm::mat4& rhs)
        {
      		if (!node.IsSequence() || node.size() != 16)
				return false;

            rhs[0][0] = node[0].as<float>();
            rhs[0][1] = node[1].as<float>();
            rhs[0][2] = node[2].as<float>();
            rhs[0][3] = node[3].as<float>();
            rhs[1][0] = node[4].as<float>();
            rhs[1][1] = node[5].as<float>();
            rhs[1][2] = node[6].as<float>();
            rhs[1][3] = node[7].as<float>();
            rhs[2][0] = node[8].as<float>();
            rhs[2][1] = node[9].as<float>();
            rhs[2][2] = node[10].as<float>();
            rhs[2][3] = node[11].as<float>();
            rhs[3][0] = node[12].as<float>();
            rhs[3][1] = node[13].as<float>();
            rhs[3][2] = node[14].as<float>();
            rhs[3][3] = node[15].as<float>();
            return true;
        }
    };
    template <>
    struct convert<glm::mat3>
    {
        static Node encode(const glm::mat3& rhs)
        {
            Node node;
            node.push_back(rhs[0][0]);
            node.push_back(rhs[0][1]);
            node.push_back(rhs[0][2]);
            node.push_back(rhs[1][0]);
            node.push_back(rhs[1][1]);
            node.push_back(rhs[1][2]);
            node.push_back(rhs[2][0]);
            node.push_back(rhs[2][1]);
            node.push_back(rhs[2][2]);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, glm::mat3& rhs)
        {
    		if (!node.IsSequence() || node.size() != 9)
				return false;

            rhs[0][0] = node[0].as<float>();
            rhs[0][1] = node[1].as<float>();
            rhs[0][2] = node[2].as<float>();
            rhs[1][0] = node[3].as<float>();
            rhs[1][1] = node[4].as<float>();
            rhs[1][2] = node[5].as<float>();
            rhs[2][0] = node[6].as<float>();
            rhs[2][1] = node[7].as<float>();
            rhs[2][2] = node[8].as<float>();
            return true;
        }
    };
    template <>
    struct convert<glm::vec4>
    {
        static Node encode(const glm::vec4& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, glm::vec4& rhs)
        {
			if (!node.IsSequence() || node.size() != 4)
			    return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };

    template <>
    struct convert<glm::vec3>
    {
        static Node encode(const glm::vec3& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, glm::vec3& rhs)
        {
			if (!node.IsSequence() || node.size() != 3)
				return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };
    template <>
    struct convert<glm::vec2>
    {
        static Node encode(const glm::vec2& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, glm::vec2& rhs)
        {
			if (!node.IsSequence() || node.size() != 2)
				return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };
} // namespace YAML

namespace glm
{
    inline std::string tostring(glm::mat4 &v)
    {
        std::string out = "[[" + std::to_string(v[0][0]) + ", " + std::to_string(v[0][1]) + ", " + std::to_string(v[0][2]) + ", " + std::to_string(v[0][3]) + "],["

                          + std::to_string(v[1][0]) + ", " + std::to_string(v[1][1]) + ", " + std::to_string(v[1][2]) + ", " + std::to_string(v[1][3]) + "],["

                          + std::to_string(v[2][0]) + ", " + std::to_string(v[2][1]) + ", " + std::to_string(v[2][2]) + ", " + std::to_string(v[2][3]) + "],["

                          + std::to_string(v[3][0]) + ", " + std::to_string(v[3][1]) + ", " + std::to_string(v[3][2]) + ", " + std::to_string(v[3][3]) + "]]";
        return out;
    }
    inline std::string tostring(glm::mat3 &v)
    {
        std::string out = "[[" + std::to_string(v[0][0]) + ", " + std::to_string(v[0][1]) + ", " + std::to_string(v[0][2]) + "],["

                          + std::to_string(v[1][0]) + ", " + std::to_string(v[1][1]) + ", " + std::to_string(v[1][2]) + "],["

                          + std::to_string(v[2][0]) + ", " + std::to_string(v[2][1]) + ", " + std::to_string(v[2][2]) + "],[";
        return out;
    }
    inline std::string tostring(glm::vec4 &v)
    {
        std::string out = "[" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ", " + std::to_string(v.w) + ")";
        return out;
    }
    inline std::string tostring(glm::vec3 &v)
    {
        std::string out = "[" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")";
        return out;
    }
    inline std::string tostring(glm::vec2 &v)
    {
        std::string out = "[" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
        return out;
    }
    inline glm::vec4 vec4_from_string(std::string &str)
    {
        VM_CORE_ASSERT(str.substr(0, 4) == "vec4", "glm::vec4_from_string error:" + str);
        vec4 out;
        int sep1 = str.find_first_of(',');
        int sep2 = str.substr(sep1, str.size()).find_first_of(',');
        int sep3 = str.substr(sep2, str.size()).find_first_of(',');
        std::string a = str.substr(5, sep1);
        std::string b = str.substr(sep1 + 1, sep2 - sep1);
        std::string c = str.substr(sep2 + 1, sep2 - sep2);
        std::string d = str.substr(sep3 + 1, str.find_first_of(')') - sep3);
        out[0] = stof(a);
        out[1] = stof(b);
        out[2] = stof(c);
        out[3] = stof(d);
        return out;
    };

    inline glm::vec3 vec3_from_string(std::string &str)
    {
        VM_CORE_ASSERT(str.substr(0, 4) == "vec3", "glm::vec3_from_string error:" + str);
        vec4 out;
        int sep1 = str.find_first_of(',');
        int sep2 = str.substr(sep1, str.size()).find_first_of(',');
        int sep3 = str.substr(sep2, str.size()).find_first_of(',');
        std::string a = str.substr(5, sep1);
        std::string b = str.substr(sep1 + 1, sep2 - sep1);
        std::string c = str.substr(sep2 + 1, sep3 - sep1);
        std::string d = str.substr(sep3 + 1, str.find_first_of(')') - sep2);
        out[0] = stof(a);
        out[1] = stof(b);
        out[2] = stof(c);
        out[3] = stof(d);
        return out;
    };

    inline glm::vec2 vec2_from_string(std::string &str)
    {
        VM_CORE_ASSERT(str.substr(0, 4) == "vec2", "glm::vec2_from_string error:" + str);
        vec2 out;
        int sep = str.find_first_of(',');
        std::string a = str.substr(4, sep - 4);
        std::string b = str.substr(sep + 1, str.find_first_of(')') - sep);
        out.x = stof(a);
        out.y = stof(b);
        return out;
    };

    inline glm::mat4 mat4_from_string(std::string &str)
    {
        VM_CORE_ASSERT(str.substr(0, 6) == "mat4x4", "glm::mat4_from_string error:" + str);
        mat4 out;
        int pos = 0;
        int index = 0;
        std::string v;

        for (char c : str.substr(8, str.size()))
        // Skips mat4x4 and -1 from end (not important)
        // mat4x4((0.000000, 0.000000, 0.000000, 0.000000),(0.000000, 0.000000, 0.000000, 0.000000),(0.000000, 0.000000, 0.000000, 0.000000),(0.000000, 0.000000, 0.000000, 0.000000))
        {
            if (c == '.' || isdigit(c))
            {
                v += c;
            }
            else if (c == ',' && v.size() > 1)
            {
                out[index][pos] = stof(v);
                v.clear();
                pos++;
                if (pos >= 3)
                    pos = 0;
            }
            else if (c == '(')
            {
                index++;
            }
        }
        return out;
    };

} // namespace glm
