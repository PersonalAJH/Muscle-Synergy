/*	WARNING: COPYRIGHT (C) 2018 XSENS TECHNOLOGIES OR SUBSIDIARIES WORLDWIDE. ALL RIGHTS RESERVED.
	THIS FILE AND THE SOURCE CODE IT CONTAINS (AND/OR THE BINARY CODE FILES FOUND IN THE SAME
	FOLDER THAT CONTAINS THIS FILE) AND ALL RELATED SOFTWARE (COLLECTIVELY, "CODE") ARE SUBJECT
	TO A RESTRICTED LICENSE AGREEMENT ("AGREEMENT") BETWEEN XSENS AS LICENSOR AND THE AUTHORIZED
	LICENSEE UNDER THE AGREEMENT. THE CODE MUST BE USED SOLELY WITH XSENS PRODUCTS INCORPORATED
	INTO LICENSEE PRODUCTS IN ACCORDANCE WITH THE AGREEMENT. ANY USE, MODIFICATION, COPYING OR
	DISTRIBUTION OF THE CODE IS STRICTLY PROHIBITED UNLESS EXPRESSLY AUTHORIZED BY THE AGREEMENT.
	IF YOU ARE NOT AN AUTHORIZED USER OF THE CODE IN ACCORDANCE WITH THE AGREEMENT, YOU MUST STOP
	USING OR VIEWING THE CODE NOW, REMOVE ANY COPIES OF THE CODE FROM YOUR COMPUTER AND NOTIFY
	XSENS IMMEDIATELY BY EMAIL TO INFO@XSENS.COM. ANY COPIES OR DERIVATIVES OF THE CODE (IN WHOLE
	OR IN PART) IN SOURCE CODE FORM THAT ARE PERMITTED BY THE AGREEMENT MUST RETAIN THE ABOVE
	COPYRIGHT NOTICE AND THIS PARAGRAPH IN ITS ENTIRETY, AS REQUIRED BY THE AGREEMENT.
*/

#ifndef ALIASCAST_H
#define ALIASCAST_H

#ifdef __cplusplus
#ifndef XSENS_MATH_FIRMWARE

#include <type_traits>

namespace Internal
{
	/*! \class AliasCaster
		Alias caster can be used to reinterpret a memory locatation as a different type without breaking strict aliasing rules.
		For example casting a pointer to a struct to a pointer to a uint16_t.
		AliasCaster only supports casting pointers.
		Example:
		MyStruct myStruct;
		uint16_t* myUint16ptr = AliasCaster<uint16_t*, MyStruct>(&myStruct);
		uint16_t firstUint = *myUint16ptr;
		The helper function alias_cast (see below) is provided for easier usage
		\note Strictly speaking, according to the standard, assigning to alias.from and the reading alias.to is undefined behaviour
		\note Putting only pointers in the union an invalid solution according to the link below
		http://cellperformance.beyond3d.com/articles/2006/06/understanding-strict-aliasing.html
		http://blog.regehr.org/archives/959

		The chosen solution is to cast the source pointer to a pointer to a union of the 'base' types of the source and destination pointers
		and then return the adress of the destination field of the union.
	*/
	template <typename U, typename V>
	class AliasCaster {
	public:
		typedef U to_type; //!< This is a pointer to type
		typedef V from_type; //!< This is a pointer from type
		typedef typename std::remove_pointer<to_type>::type base_to_type; //!< This is a base pointer to type
		typedef typename std::remove_pointer<from_type>::type base_from_type; //!< This is a base pointer from type

		static_assert(std::is_pointer<to_type>::value && std::is_pointer<from_type>::value, "alias_caster requires pointer types as arguments");
		static_assert(!std::is_const<base_from_type>::value || (std::is_const<base_from_type>::value && std::is_const<base_to_type>::value), "alias_caster requires a const destination type here");

		static to_type cast(from_type from) {return &(reinterpret_cast<AliasType*>(from)->to);} //!< This is a pointer type cast
	private:
		// The union to cast the from_type to
		typedef union  {
			base_from_type from;
			base_to_type to;
		} AliasUnion;

		// Depending on the const-ness of the from_type, we need to cast to a const union or not
		typedef typename std::conditional<
			std::is_const<base_from_type>::value,
			typename std::add_const<AliasUnion>::type,
			AliasUnion
		>::type AliasType;
	};
} // namespace Internal

/*! Casts one pointer to another without breaking strict aliasing rules.
	\see Internal::AliasCaster
	Example:
	MyStruct myStruct;
	uint16_t* myUint16ptr = alias_cast<uint16_t*>(&myStruct);
	uint16_t firstUint = *myUint16ptr;
*/
template <typename U, typename V>
U alias_cast(V fromPtr) {
	return Internal::AliasCaster<U, V>::cast(fromPtr);
}

#endif // XSENS_MATH_FIRMWARE

#endif // __cplusplus

#endif // ALIASCAST_H