#pragma once

#include <memory>

namespace app::presenter
{

class IDocument;

using IDocumentRawPtr = IDocument*;
using IDocumentPtr = std::unique_ptr<IDocument>;
using IDocumentSharedPtr = std::shared_ptr<IDocument>;

} // namespace app::presenter
