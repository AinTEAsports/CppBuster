#include <cpr/response.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <thread>

#include <cpr/cpr.h>
#include "cpparser.cpp"

#include "utils.cpp"



void check_subfolder(std::string url, std::string subfolder) {
	/* std::string SPACE_AFTER_PERCENTAGE = "100.00%".size() + 1; */

	std::string whole_url = url + '/' + subfolder;

	cpr::Response response = cpr::Get(cpr::Url{whole_url});
	bool exists = utils::STATUS_CODES_INFOS[response.status_code].first;

	std::string text = "==> " + Color::bold() + whole_url + Color::end();

	if (exists) {
		std::cout << std::setw(80) << std::left << text << Color::bold() << "[" << Color::green() << response.status_code << Color::end() << Color::bold() << "]\n" << Color::end();
	}
}


int main(int argc, char** argv) {
	Parser parser("A GoBuster like tool, but written in C++");

	parser.addArgument(
		"-u",
		"--url",
		"url",
		Parser::STORE_ONE_VALUE,
		"The target URL"
	);

	parser.addArgument(
		"-w",
		"--wordlist",
		"wordlist",
		Parser::STORE_ONE_VALUE,
		"The wordlist used"
	);

	auto args = parser.parseArgs(argc, argv);

	std::string url = args["url"].String;
	std::string wordlist = args["wordlist"].String;

	if (!utils::url_exists(url)) {
		std::string error_text = Color::red() + Color::bold() +"[!] URL does not exists or is unreachable" + Color::end();
		std::cout << error_text << std::endl;

		exit(1);
	}


	if (utils::is_last_char(url, '/')) {
		url = utils::slice_copy(url, 0, url.size()-1);
	}


	// Just for lisibility
	std::cout << '\n';

	int done_url = 0;
	std::vector<std::string> lines = utils::read_lines(wordlist);
	int TOTAL_URL = lines.size();
	std::thread current_thread;

	for (std::string subfolder: lines) {
		done_url++;

		if (utils::startswith(subfolder, "#") || utils::startswith(subfolder, "?")) continue;

		std::thread current_thread(check_subfolder, url, subfolder);
		current_thread.join();

		/* check_subfolder(url, subfolder); */

		std::cout << "Done: [" << done_url << "/" << TOTAL_URL << "] " << utils::round(utils::percentage(done_url, TOTAL_URL)) << "% \r";
	}

	std::cout << "Done: [" << done_url << '/' << TOTAL_URL << "] 100.0%" << std::endl;

	return 0;
}
