
#include "team.h"
#include <iostream>

namespace seneca {
    Team::Team() {}
    Team::Team(const char* name) : m_name(name) {}
    Team::Team(const Team& other) {
        m_name = other.m_name;
        for (const auto& member : other.m_members) {
            m_members.push_back(member->clone());
        }
    }
    Team& Team::operator=(const Team& other) {
        if (this != &other) {
            m_name = other.m_name;
            for (const auto& member : m_members) {
                delete member;
            }
            m_members.clear();
            for (const auto& member : other.m_members) {
                m_members.push_back(member->clone());
            }
        }
        return *this;
    }
    Team::Team(Team&& other) noexcept {
        m_name = std::move(other.m_name);
        m_members = std::move(other.m_members);
    }
    Team& Team::operator=(Team&& other) noexcept {
        if (this != &other) {
            m_name = std::move(other.m_name);
            m_members = std::move(other.m_members);
        }
        return *this;
    }
    Team::~Team() {
        for (auto& member : m_members) {
            delete member;
        }
    }
    void Team::addMember(const Character* c) {
        for (const auto& member : m_members) {
            if (member->getName() == c->getName()) {
                return; 
            }
        }
        m_members.push_back(c->clone());
    }
    void Team::removeMember(const std::string& name) {
        for (auto it = m_members.begin(); it != m_members.end(); ++it) {
            if ((*it)->getName() == name) {
                delete* it;
                m_members.erase(it);
                break;
            }
        }
    }
    Character* Team::operator[](size_t idx) const {
        if (idx < m_members.size()) {
            return m_members[idx];
        }
        return nullptr;
    }
    void Team::showMembers() const {
        if (m_members.empty()) {
            std::cout << "No team.\n";
        }
        else {
            std::cout << "[Team] " << m_name << "\n";
            for (size_t i = 0; i < m_members.size(); ++i) {
                std::cout << "    " << i + 1 << ": " << *m_members[i] << "\n";
            }
        }
    }
}