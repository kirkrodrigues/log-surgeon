#ifndef LOG_SURGEON_FINITE_AUTOMATA_TAGGED_TRANSITION
#define LOG_SURGEON_FINITE_AUTOMATA_TAGGED_TRANSITION

#include <cstdint>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>

#include <fmt/format.h>

#include <log_surgeon/finite_automata/RegexNFAStateType.hpp>

namespace log_surgeon::finite_automata {
template <typename NFAStateType>
class PositiveTaggedTransition {
public:
    PositiveTaggedTransition(uint32_t const tag, NFAStateType const* dest_state)
            : m_tag{tag},
              m_dest_state{dest_state} {}

    [[nodiscard]] auto get_tag() const -> uint32_t { return m_tag; }

    [[nodiscard]] auto get_dest_state() const -> NFAStateType const* { return m_dest_state; }

    /**
     * @param state_ids A map of states to their unique identifiers.
     * @return A string representation of the positive tagged transition on success.
     * @return std::nullopt if `m_dest_state` is not in `state_ids`.
     */
    [[nodiscard]] auto serialize(std::unordered_map<NFAStateType const*, uint32_t> const& state_ids
    ) const -> std::optional<std::string> {
        auto const state_id_it = state_ids.find(m_dest_state);
        if (state_id_it == state_ids.end()) {
            return std::nullopt;
        }
        return fmt::format("{}[{}]", state_id_it->second, m_tag);
    }

private:
    uint32_t m_tag;
    NFAStateType const* m_dest_state;
};

template <typename NFAStateType>
class NegativeTaggedTransition {
public:
    NegativeTaggedTransition(std::set<uint32_t> tags, NFAStateType const* dest_state)
            : m_tags{std::move(tags)},
              m_dest_state{dest_state} {}

    [[nodiscard]] auto get_tags() const -> std::set<uint32_t> const& { return m_tags; }

    [[nodiscard]] auto get_dest_state() const -> NFAStateType const* { return m_dest_state; }

    /**
     * @param state_ids A map of states to their unique identifiers.
     * @return A string representation of the negative tagged transition on success.
     * @return std::nullopt if `m_dest_state` is not in `state_ids`.
     */
    [[nodiscard]] auto serialize(std::unordered_map<NFAStateType const*, uint32_t> const& state_ids
    ) const -> std::optional<std::string> {
        auto const state_id_it = state_ids.find(m_dest_state);
        if (state_id_it == state_ids.end()) {
            return std::nullopt;
        }
        return fmt::format("{}[{}]", state_id_it->second, fmt::join(m_tags, ","));
    }

private:
    std::set<uint32_t> m_tags;
    NFAStateType const* m_dest_state;
};
}  // namespace log_surgeon::finite_automata

#endif  // LOG_SURGEON_FINITE_AUTOMATA_TAGGED_TRANSITION
