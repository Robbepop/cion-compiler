#ifndef CION_AST_CALL_EXPRESSION_HEADER
#define CION_AST_CALL_EXPRESSION_HEADER

#include "ast/expression.hpp"
#include "ast/expression_list.hpp"

#include <string>
#include <memory>

namespace cion {
namespace ast {
	class CallExpression : public Expression {
	public:
		CallExpression(
			std::unique_ptr<Expression> callee,
			std::unique_ptr<ExpressionList> args);

		CallExpression(
			std::unique_ptr<Expression> callee);

		Expression & callee();
		Expression const& callee() const;

		ExpressionList & args();
		ExpressionList const& args() const;

		virtual void accept(MutatingCompilerPass & pass) override;
		virtual void accept(CompilerPass & pass) const override;

	private:
		std::unique_ptr<Expression> m_callee;
		std::unique_ptr<ExpressionList> m_args;
	};
} // namespace ast
} // namespace cion

#endif // CION_AST_CALL_EXPRESSION_HEADER