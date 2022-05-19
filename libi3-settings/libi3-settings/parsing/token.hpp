#pragma once

namespace i3s::parsing
{
	enum struct token
	{
		bindsym,
		exec,

		plus,

		identifier,
		command,
		keysym,
		
		integer_literal,
		string_literal
	};
}
