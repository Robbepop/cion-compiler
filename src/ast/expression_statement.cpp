#include "ast/expression_statement.hpp"

#include <utility>
#include <cassert>

namespace cion {
namespace ast {

	ExpressionStatement::ExpressionStatement(
		std::unique_ptr<Expression> expr
	):
		m_expr{std::move(expr)}
	{}

	Expression & ExpressionStatement::expr() {
		assert(m_expr != nullptr);
		return *m_expr;
	}

	Expression const& ExpressionStatement::expr() const {
		assert(m_expr != nullptr);
		return *m_expr;
	}

	void ExpressionStatement::accept(MutatingCompilerPass & pass) {
		pass.visit(*this);
	}

	void ExpressionStatement::accept(CompilerPass & pass) const {
		pass.visit(*this);
	}

} // namespace ast
} // namespace cion