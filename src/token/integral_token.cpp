#include "token/integral_token.hpp"

#include <stdexcept>
#include <iostream>

namespace cion {
	IntegralToken::IntegralToken(
		TokenType const& token_type,
		SourceLocation const& start_loc,
		SourceLocation const& end_loc,
		IntegralToken::value_type value
	) :
		Token{token_type, start_loc, end_loc},
		m_value{value}
	{}

	IntegralToken::IntegralToken(
		TokenType const& token_type,
		SourceLocation const& start_loc,
		SourceLocation const& end_loc,
		std::string value
	) try :
		Token{token_type, start_loc, end_loc},
		m_value{std::stol(value)}
	{} catch (std::invalid_argument const& e) {
		std::cerr << "read IntegralToken with invalid value format: " << e.what() << "\n";
	}  catch (std::out_of_range const& e) {
		std::cerr << "read IntegralToken with its value out of bounds of its binary representation: " << e.what() << "\n";
	}

	IntegralToken::value_type IntegralToken::get_integral() const {
		return m_value;
	}
} // namespace cion
