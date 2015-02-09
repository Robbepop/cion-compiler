#include "ast/nothing_type.hpp"

namespace cion {
namespace ast {

	void NothingType::accept(CompilerPass & pass) {
		pass.visit(*this);
	}

} // namespace ast
} // namespace cion
