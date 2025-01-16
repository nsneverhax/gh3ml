#pragma once

#include <cstdint>

#include <string>

namespace gh3ml
{
	enum class FunctionCallingConvention
	{

	};

	class ArgumentDescriptor
	{
	private:
		std::string m_Type = "";
		std::string m_Name = "";
		bool m_optional = "";
		std::string m_defaultValue = "";
	public:
		ArgumentDescriptor(const std::string& type, const std::string& name);
		ArgumentDescriptor(const std::string& type, const std::string& name, bool isOptional, const std::string& defaultValue);

		/// <summary>
		/// Gets the type of the Argument
		/// </summary>
		/// <returns></returns>
		const std::string& GetType() const;
		/// <summary>
		/// Gets the name< of the argument
		/// </summary>
		/// <returns></returns>
		const std::string& GetName() const;

		/// <summary>
		/// Is the argument optional?
		/// </summary>
		/// <returns></returns>
		const bool IsOption() const;

		/// <summary>
		/// Gets the default value of the argument
		/// </summary>
		/// <returns></returns>
		const std::string& GetDefaultValue() const;


	};
}