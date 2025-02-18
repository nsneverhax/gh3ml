#include <GH3/Script/CComponentType.hpp>

#include <format>

std::string GH3::Script::to_string(CComponentType type)
{
	switch (type)
	{
	case GH3::Script::CComponentType::QFlagNone:
		return "QFlagNone";
	case GH3::Script::CComponentType::QFlagStructItem:
		return "QFlagStructItem";
	case GH3::Script::CComponentType::QTypeInt:
		return "QTypeInt";
	case GH3::Script::CComponentType::QTypeFloat:
		return "QTypeFloat";
	case GH3::Script::CComponentType::QTypeCString:
		return "QTypeCString";
	case GH3::Script::CComponentType::QTypeWString:
		return "QTypeWString";
	case GH3::Script::CComponentType::QTypePair:
		return "QTypePair";
	case GH3::Script::CComponentType::QTypeVector:
		return "QTypeVector";
	case GH3::Script::CComponentType::QTypeScript:
		return "QTypeScript";
	case GH3::Script::CComponentType::QTypeCFunc:
		return "QTypeCFunc";
	case GH3::Script::CComponentType::QTypeUnk9:
		return "QTypeUnk9";
	case GH3::Script::CComponentType::QTypeQbStruct:
		return "QTypeQbStruct";
	case GH3::Script::CComponentType::QTypeQbArray:
		return "QTypeQbArray";
	case GH3::Script::CComponentType::QTypeQbKey:
		return "QTypeQbKey";
	case GH3::Script::CComponentType::QTypeQbKeyRef:
		return "QTypeQbKeyRef";
	case GH3::Script::CComponentType::QTypeUnk20:
		return "QTypeUnk20";
	case GH3::Script::CComponentType::QTypeUnk21:
		return "QTypeUnk21";
	case GH3::Script::CComponentType::QTypeBinaryTree1:
		return "QTypeBinaryTree1";
	case GH3::Script::CComponentType::QTypeBinaryTree2:
		return "QTypeBinaryTree2";
	case GH3::Script::CComponentType::QTypeStringPointer:
		return "QTypeStringPointer";
	case GH3::Script::CComponentType::QTypeMap:
		return "QTypeMap";
	default:
		return std::format("Unknown CComponentType: {:X}", static_cast<uint8_t>(type));
	}
}