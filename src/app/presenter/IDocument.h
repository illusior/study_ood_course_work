#pragma once

#include "IDocument_fwd.h"

namespace app::presenter
{

class IDocument
{
public:
	virtual bool CanUndo() const noexcept = 0;
	virtual bool CanRedo() const noexcept = 0;

	virtual ~IDocument() = default;
};

} // namespace app::presenter
