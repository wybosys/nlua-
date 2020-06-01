﻿#include "core.hpp"
#include "variant.hpp"
#include <math.h>
#include "nlua++.hpp"

NLUA_BEGIN

Variant::VT FromCom(com::Variant::VT vt) {
    switch (vt) {
        case com::Variant::VT::INT:
        case com::Variant::VT::UINT:
        case com::Variant::VT::LONG:
        case com::Variant::VT::ULONG:
        case com::Variant::VT::SHORT:
        case com::Variant::VT::USHORT:
        case com::Variant::VT::LONGLONG:
        case com::Variant::VT::ULONGLONG:
        case com::Variant::VT::CHAR:
        case com::Variant::VT::UCHAR:
            return Variant::VT::INTEGER;
        case com::Variant::VT::FLOAT:
        case com::Variant::VT::DOUBLE:
            return Variant::VT::NUMBER;
        case com::Variant::VT::OBJECT:
        case com::Variant::VT::POINTER:
            return Variant::VT::POINTER;
        case com::Variant::VT::BOOLEAN:
            return Variant::VT::BOOLEAN;
        case com::Variant::VT::STRING:
            return Variant::VT::STRING;
    }
    return Variant::VT::NIL;
}

Variant::Variant()
        : vt(VT::NIL) {
}

Variant::Variant(integer v)
        : vt(VT::INTEGER), _var(v) {
}

Variant::Variant(number v)
        : vt(VT::NUMBER), _var(v) {
}

Variant::Variant(bool v)
        : vt(VT::BOOLEAN), _var(v) {
}

Variant::Variant(string const &v)
        : vt(VT::STRING), _var(v) {
}

Variant::Variant(char const *v)
        : vt(VT::STRING), _var(v) {
}

Variant::Variant(void *v)
        : vt(VT::POINTER), _var(v) {
}

Variant::Variant(nullptr_t)
        : vt(VT::POINTER), _var(nullptr) {
}

Variant::Variant(com::Variant const &v)
        : vt(FromCom(v.vt)), _var(v) {
}

Variant::Variant(shared_ptr<Object> const& r)
    : vt(VT::OBJECT), _var(*r->toVariant())
{}

integer Variant::toInteger() const {
    switch (_var.vt) {
        case com::Variant::VT::INT:
            return _var.toInt();
        case com::Variant::VT::UINT:
            return _var.toUInt();
        case com::Variant::VT::LONG:
            return _var.toLong();
        case com::Variant::VT::ULONG:
            return _var.toULong();
        case com::Variant::VT::SHORT:
            return _var.toShort();
        case com::Variant::VT::USHORT:
            return _var.toUShort();
        case com::Variant::VT::LONGLONG:
            return (integer) _var.toLonglong();
        case com::Variant::VT::ULONGLONG:
            return (integer) _var.toULonglong();
        case com::Variant::VT::CHAR:
            return _var.toChar();
        case com::Variant::VT::UCHAR:
            return _var.toUChar();
        case com::Variant::VT::BOOLEAN:
            return _var.toBool();
        case com::Variant::VT::FLOAT:
            return (integer) round(_var.toFloat());
        case com::Variant::VT::DOUBLE:
            return (integer) round(_var.toDouble());
    }
    return 0;
}

number Variant::toNumber() const {
    switch (_var.vt) {
        case com::Variant::VT::FLOAT:
            return _var.toFloat();
        case com::Variant::VT::DOUBLE:
            return _var.toDouble();
    }
    return toInteger();
}

bool Variant::toBool() const {
    if (_var.vt == com::Variant::VT::BOOLEAN)
        return _var.toBool();
    return toNumber() != 0;
}

string const &Variant::toString() const {
    return _var.toString();
}

void *Variant::toPointer() const {
    switch (_var.vt) {
        case com::Variant::VT::OBJECT:
            return _var.toObject();
        case com::Variant::VT::POINTER:
            return _var.toPointer();
    }
    return nullptr;
}

NLUA_END
