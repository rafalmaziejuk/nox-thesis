#pragma once

#include <nox/input_identifiers.h>

namespace NOX {

    class KeyEvent {
      public:
        KeyEvent(Key key, Action action) : m_key(key),
                                           m_action(action) {}

        Key getKey() const { return m_key; }
        Action getAction() const { return m_action; }

      private:
        Key m_key;
        Action m_action;
    };

} // namespace NOX
