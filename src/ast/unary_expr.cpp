#include "ast/unary_expr.hpp"

#include "cion_token_types.hpp"

#include <stdexcept>
#include <utility>
#include <cassert>

namespace cion {
namespace ast {

//////////////////////////////////////////////////////////////////////////////////////////
/// UnaryExpr
//////////////////////////////////////////////////////////////////////////////////////////

	UnaryExpr::UnaryExpr(
		std::unique_ptr<Expr> p_expr
	):
		m_expr{std::move(p_expr)}
	{}

	Expr & UnaryExpr::expr() {
		assert(m_expr != nullptr);
		return *m_expr;
	}

	Expr const& UnaryExpr::expr() const {
		assert(m_expr != nullptr);
		return *m_expr;
	}

	void UnaryExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// BitNegateExpr
//////////////////////////////////////////////////////////////////////////////////////////

	UnaryExpr::Kind BitNegateExpr::kind() const {
		return UnaryExpr::Kind::bit_negate;
	}

	void BitNegateExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// LogicalNegateExpr
//////////////////////////////////////////////////////////////////////////////////////////

	UnaryExpr::Kind LogicalNegateExpr::kind() const {
		return UnaryExpr::Kind::logical_negate;
	}

	void LogicalNegateExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// PlusExpr
//////////////////////////////////////////////////////////////////////////////////////////

	UnaryExpr::Kind PlusExpr::kind() const {
		return UnaryExpr::Kind::plus;
	}

	void PlusExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// MinusExpr
//////////////////////////////////////////////////////////////////////////////////////////

	UnaryExpr::Kind MinusExpr::kind() const {
		return UnaryExpr::Kind::minus;
	}

	void MinusExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// IncrementExpr
//////////////////////////////////////////////////////////////////////////////////////////

	UnaryExpr::Kind IncrementExpr::kind() const {
		return UnaryExpr::Kind::increment;
	}

	void IncrementExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// DecrementExpr
//////////////////////////////////////////////////////////////////////////////////////////

	UnaryExpr::Kind DecrementExpr::kind() const {
		return UnaryExpr::Kind::decrement;
	}

	void DecrementExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// PostIncrementExpr
//////////////////////////////////////////////////////////////////////////////////////////

	UnaryExpr::Kind PostIncrementExpr::kind() const {
		return UnaryExpr::Kind::post_increment;
	}

	void PostIncrementExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// PostDecrementExpr
//////////////////////////////////////////////////////////////////////////////////////////

	UnaryExpr::Kind PostDecrementExpr::kind() const {
		return UnaryExpr::Kind::post_decrement;
	}

	void PostDecrementExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

} // namespace ast
} // namespace cion
