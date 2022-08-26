#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

#include <cpr/cpr.h>


namespace utils {
	/* Example of ow the map is organised:
	{
		status_code: (
			exists,
			description
		)
	}
	*/

	// Other infos are in ~/Code/Github/website-sublister/utils.py
	std::map<int, std::pair<bool, std::string>> STATUS_CODES_INFOS = {
		{200, {true, "OK"}},
	};


	float percentage(float first_number, float second_number) {
		return (first_number/second_number) * 100.0;
	}


	std::string read_file(std::string filename) {
        std::string line = "";
        std::string content = "";

        std::ifstream file;
        file.open(filename);

        while (file >> line) content += line + '\n';

        file.close();

        return content;
        }


        std::vector<std::string> read_lines(std::string filename) {
                std::vector<std::string> lines = {};
                std::string line = "";

                std::ifstream file;
                file.open(filename);

                while (file >> line) lines.push_back(line);

                file.close();

                return lines;
        }


        bool is_last_char(std::string string, char to_verify) {
                char last_char = string[string.size()-1];
                return last_char == to_verify;
        }


        std::string slice_copy(std::string string, int from, int to) {
                std::string result = "";

                for (int i = from; i < to; i++) {
                        result += string[i];
                }

                return result;
        }


		bool url_exists(std::string url) {
			return cpr::Get(cpr::Url{url}).status_code != 0;
		}


		float round(float number) {
			float value = (int) (number * 100 + .5);
			return (float) value / 100;
		}


		bool startswith(std::string string, std::string to_verify) {
			return (string.rfind(to_verify, 0) == 0);
		}
}


class Color {
	public:
		static std::string green() {
			return "\033[92m";
		}


		static std::string red() {
			return "\033[91m";
		}


		static std::string bold() {
			return "\033[1m";
		}


		static std::string end() {
			return "\033[0m";
		}
};

