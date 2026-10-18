#include <cstdint>
#include <stdexcept>

namespace demo {
using Cents = std::int64_t;

enum class Zone { Local, Remote };

struct Shipment {
    Cents subtotal;
    int grams;
    Zone zone;
    bool is_regular_customer = false;
};

class DeliveryPolicy {
public:
    Cents quote(const Shipment& s) const {
        if (s.subtotal < 0) {
            throw std::invalid_argument("negative order subtotal");
        }
        if (s.grams < 1 || s.grams > 50000) {
            throw std::invalid_argument("invalid weight");
        }

        Cents fee = 0;
        Cents threshold = 500000;
        Cents base_local = 30000;
        Cents base_remote = 70000;

        if (s.is_regular_customer) {
            threshold = 300000;
            base_remote = 50000;
        }

        if (s.zone == Zone::Remote) {
            fee = base_remote;
        } else {
            fee = (s.subtotal >= threshold) ? 0 : base_local;
        }

        if (s.grams > 20000) {
            if (s.zone == Zone::Local) {
                int extra_blocks = (s.grams - 20000 + 4999) / 5000;
                fee += extra_blocks * 100000; 
            } else {
                int extra_kg = (s.grams - 20000 + 999) / 1000;
                fee += extra_kg * 30000; 
            }
        }

        return fee;
    }
};
}