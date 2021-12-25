#pragma once

namespace Me
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t const a_id);
		UUID(UUID const&) = default;

		operator uint64_t() const { return m_guid; }
	private:
		uint64_t m_guid;
	};
}