#ifndef CION_AST_EXPR_STMNT_HEADER
#define CION_AST_EXPR_STMNT_HEADER

#include "cion/ast/stmnt.hpp"
#include "cion/ast/expr.hpp"

#include <memory>

namespace cion {
namespace ast {

	class ExprStmnt : public Stmnt {
	public:
		ExprStmnt(std::unique_ptr<Expr> expr);

		Expr & expr();
		Expr const& expr() const;

		virtual void accept(IASTVisitor & pass) override;

	private:
		std::unique_ptr<Expr> m_expr;
	};

} // namespace ast
} // namespace cion

#endif // CION_AST_EXPR_STMNT_HEADER
