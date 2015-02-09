#include "ast/binary_assign_expr.hpp"

#include "cion_token_types.hpp"

#include <cassert>
#include <stdexcept>
#include <utility>

namespace cion {
namespace ast {


//////////////////////////////////////////////////////////////////////////////////////////
/// BinaryAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	void BinaryAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// AssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind AssignExpr::kind() const {
		return BinaryExpr::Kind::assign;
	}

	void AssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// AddAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind AddAssignExpr::kind() const {
		return BinaryExpr::Kind::add_assign;
	}

	void AddAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// SubtractAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind SubtractAssignExpr::kind() const {
		return BinaryExpr::Kind::subtract_assign;
	}

	void SubtractAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// MultiplyAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind MultiplyAssignExpr::kind() const {
		return BinaryExpr::Kind::multiply_assign;
	}

	void MultiplyAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// DivideAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind DivideAssignExpr::kind() const {
		return BinaryExpr::Kind::divide_assign;
	}

	void DivideAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// ModuloAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind ModuloAssignExpr::kind() const {
		return BinaryExpr::Kind::modulo_assign;
	}

	void ModuloAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// LogicalOrAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind LogicalOrAssignExpr::kind() const {
		return BinaryExpr::Kind::logical_or_assign;
	}

	void LogicalOrAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// LogicalAndAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind LogicalAndAssignExpr::kind() const {
		return BinaryExpr::Kind::logical_and_assign;
	}

	void LogicalAndAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// BitOrAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind BitOrAssignExpr::kind() const {
		return BinaryExpr::Kind::bit_or_assign;
	}

	void BitOrAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// BitXorAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind BitXorAssignExpr::kind() const {
		return BinaryExpr::Kind::bit_xor_assign;
	}

	void BitXorAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// BitAndAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind BitAndAssignExpr::kind() const {
		return BinaryExpr::Kind::bit_and_assign;
	}

	void BitAndAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// ShiftLeftAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind ShiftLeftAssignExpr::kind() const {
		return BinaryExpr::Kind::shift_left_assign;
	}

	void ShiftLeftAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

//////////////////////////////////////////////////////////////////////////////////////////
/// ShiftRightAssignExpr
//////////////////////////////////////////////////////////////////////////////////////////

	BinaryExpr::Kind ShiftRightAssignExpr::kind() const {
		return BinaryExpr::Kind::shift_right_assign;
	}

	void ShiftRightAssignExpr::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

} // namespace ast
} // namespace cion