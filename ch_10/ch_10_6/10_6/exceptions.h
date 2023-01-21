#pragma once
#include <string>
namespace exceptions_lib {
	class Exception {
	public:
		class Invalid {
		public:
			Invalid(const std::string& err) :error_message{ err } {}
			std::string what() { return error_message; }
		private:
			std::string error_message;
		};
		class Parse_error {
		public:
			Parse_error(const std::string& err) :error_message{ err } {}
			std::string what() { return error_message; }
		private:
			std::string error_message;
		};
	};
}