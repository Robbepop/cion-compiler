#ifndef CION_AST_POSTFIX_EXPRESSION_HEADER
#define CION_AST_POSTFIX_EXPRESSION_HEADER

#include "ast/expression.hpp"
#include "token/token_type.hpp"

#include <cstdint>
#include <memory>

namespace cion {
namespace ast {
	class PostfixExpression : public Expression {
	public:
		enum class Operator : int8_t {
			increment,
			decrement
		};

		static Operator get_operator(TokenType const& tt);

		static bool is_operator(TokenType const& tt);

		PostfixExpression(
			Operator op,
			std::unique_ptr<Expression> expr);

		PostfixExpression(
			TokenType const& tt,
			std::unique_ptr<Expression> expr);

		Operator & op();
		Operator const& op() const;

		Expression & expr();
		Expression const& expr() const;

		virtual void accept(MutatingCompilerPass & pass) override;
		virtual void accept(CompilerPass & pass) const override;

	private:
		Operator m_op;
		std::unique_ptr<Expression> m_expr;
	};
} // namespace ast
} // namespace cion

#endif // CION_AST_POSTFIX_EXPRESSION_HEADER
