#pragma once

namespace Me
{
	class UUID
	{
	public:
		UUID();
		UUID(uint32_t const a_id);
		UUID(UUID const&) = default;

		operator uint32_t() const { return m_guid; }
	private:
		uint32_t m_guid;
	};
}