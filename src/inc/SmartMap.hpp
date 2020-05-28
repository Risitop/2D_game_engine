#pragma once

#include <iterator>
#include <map>
#include <vector>

template <typename K, typename V>
class SmartMap {
 public:
  //! Default constructor
  SmartMap() : m_n_elements(0) { m_free_keys.push_back(0); }

  //! Copy constructor
  SmartMap(const SmartMap &other) = delete;

  //! Move constructor
  SmartMap(SmartMap &&other) noexcept = delete;

  //! Destructor
  virtual ~SmartMap() noexcept {}

  //! Copy assignment operator
  SmartMap &operator=(const SmartMap &other) = delete;

  //! Move assignment operator
  SmartMap &operator=(SmartMap &&other) noexcept = delete;

  size_t size() { return m_n_elements; }

  K insert(V value) {
    m_n_elements++;
    K new_id = m_free_keys.back();
    m_free_keys.pop_back();
    if (m_free_keys.size() == 0) {
      m_free_keys.push_back(m_n_elements);
    }
    m_map[new_id] = value;
    return new_id;
  }

  V get(K key) {
    typename std::map<K, V>::iterator it = m_map.find(key);
    if (it == m_map.end()) {
      throw "Unknown key.";
    }
    return it->second;
  }

  void remove(K key) {
    m_n_elements--;
    m_free_keys.push_back(key);
    m_map.erase(key);
  }

  typename std::map<K, V>::iterator begin() { return m_map.begin(); }
  typename std::map<K, V>::iterator end() { return m_map.end(); }

 protected:
 private:
  std::map<K, V> m_map;
  std::vector<K> m_free_keys;
  size_t m_n_elements;
};
