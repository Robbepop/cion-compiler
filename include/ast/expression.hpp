#ifndef CION_AST_EXPRESSION_HEADER
#define CION_AST_EXPRESSION_HEADER

#include "ast/statement.hpp"

namespace cion {
namespace ast {
	class Expression : public Statement {
	public:
		virtual void accept(MutatingCompilerPass & pass) = 0;
		virtual void accept(CompilerPass & pass) const = 0;
	};
} // namespace ast
} // namespace cion

#endif // CION_AST_EXPRESSION_HEADER