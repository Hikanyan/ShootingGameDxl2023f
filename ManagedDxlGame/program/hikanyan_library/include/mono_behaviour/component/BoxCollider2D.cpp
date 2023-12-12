#include "BoxCollider2D.h"
#include "../GameObject.h"

bool BoxCollider2D::intersects(const BoxCollider2D* other) const {
    const tnl::Vector3 own_position = owner_->get_transform().get_position();
    const tnl::Vector3 other_position = other->get_owner()->get_transform().get_position();
    return intersects(*other, own_position, other_position);
}


