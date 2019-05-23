#pragma once

#include <QSharedPointer>
#include <QMetaMethod>

template <class T, class B = QObject>
class QmlSharedPointer
    : public QObject
    , public QSharedPointer<T>
{
// Q_OBJECT macro written out
public:
    QT_WARNING_PUSH
    Q_OBJECT_NO_OVERRIDE_WARNING
    static const QMetaObject staticMetaObject;
    QT_TR_FUNCTIONS
private:
    Q_OBJECT_NO_ATTRIBUTES_WARNING
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **);
    QT_WARNING_POP
    struct QPrivateSignal {};
    QT_ANNOTATE_CLASS(qt_qobject, "")
// end Q_OBJECT

private:
    void init()
    {
        // Connect all signals from the encapsulated item to the QmlSharedPointer
        // Skip QObject's signals (e.g. destroyed)
        const int qObjectMethodCount = QObject::staticMetaObject.methodCount();
        for (int i = qObjectMethodCount; i < T::staticMetaObject.methodCount(); i++)
        {
            auto incomingSignal = T::staticMetaObject.method(i);
            if (incomingSignal.methodType() != QMetaMethod::Signal) continue;
            QMetaObject::connect(QmlSharedPointer<T, B>::data(), i, this, i);
        }
    }
    void deinit()
    {
        // Disconnect all signals from the encapsulated item to the QmlSharedPointer
        // Skip QObject's signals (e.g. destroyed)
        const int qObjectMethodCount = QObject::staticMetaObject.methodCount();
        for (int i = qObjectMethodCount; i < T::staticMetaObject.methodCount(); i++)
        {
            auto incomingSignal = T::staticMetaObject.method(i);
            if (incomingSignal.methodType() != QMetaMethod::Signal) continue;
            QMetaObject::disconnect(QmlSharedPointer<T, B>::data(), i, this, i);
        }
    }
    static const QMetaObject *gen_superdata();
    static const QByteArrayData *gen_stringdata();
    static const uint *gen_data();
    static const QMetaObject * const *gen_relatedMetaObjects();
    static void *gen_extradata();
    static void findAndActivateSignal(QObject *_o, int _id, void **_a);

public:
    static int dynamic_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
    {
        //qDebug() << "Welcome to dynamic_metacall on" << staticMetaObject.className();
        const int n_methods = staticMetaObject.methodCount() - staticMetaObject.superClass()->methodCount();
        const int n_properties = staticMetaObject.propertyCount() - staticMetaObject.superClass()->propertyCount();
        //qDebug() << "First off, lets call" << B::staticMetaObject.className() << "dynamic_metacall.";
        _id = parent_metacall(_o, _c, _id, _a);
        //qDebug() << "ID is now" << _id;
        if (_id < 0)
            return _id;
        if (_c == QMetaObject::InvokeMetaMethod) {
            if (_id < n_methods)
            {
                //qDebug() << "Matches" << staticMetaObject.className();
                qt_static_metacall(_o, _c, _id, _a);
            }
            else
            {
                //qDebug() << "Doesn't match" << staticMetaObject.className();
            }
            _id -= n_methods;
        } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
            if (_id < n_methods)
                *reinterpret_cast<int*>(_a[0]) = -1;
            _id -= n_methods;
        }
        else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
              || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
            qt_static_metacall(_o, _c, _id, _a);
            _id -= n_properties;
        } else if (_c == QMetaObject::QueryPropertyDesignable) {
            _id -= n_properties;
        } else if (_c == QMetaObject::QueryPropertyScriptable) {
            _id -= n_properties;
        } else if (_c == QMetaObject::QueryPropertyStored) {
            _id -= n_properties;
        } else if (_c == QMetaObject::QueryPropertyEditable) {
            _id -= n_properties;
        } else if (_c == QMetaObject::QueryPropertyUser) {
            _id -= n_properties;
        }
        return _id;
    }

    template<class Q = B>
    static
    typename std::enable_if<!std::is_same<Q, QObject>::value, int>::type
    parent_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
    {
        return B::dynamic_metacall(_o, _c, _id, _a);
    }

    template<class Q = B>
    static
    typename std::enable_if<std::is_same<Q, QObject>::value, int>::type
    parent_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
    {
        return _o->QObject::qt_metacall(_c, _id, _a);
    }

    QmlSharedPointer()
        : QSharedPointer<T>(new T())
    {
        init();
    }

    template <typename X> explicit QmlSharedPointer(X *ptr)
        : QSharedPointer<T>(ptr)
    {
        init();
    }

    template <typename X, typename Deleter> QmlSharedPointer(X *ptr, Deleter d)
        : QSharedPointer<T>(ptr, d)
    {
        init();
    }

    QmlSharedPointer(const QSharedPointer<T> &other)
        : QSharedPointer<T>(other)
    {
        init();
    }

    QmlSharedPointer(const QmlSharedPointer<T, B> &other)
        : QSharedPointer<T>(other)
    {
        init();
    }

    QmlSharedPointer(const QWeakPointer<T> &other)
        : QSharedPointer<T>(other)
    {
        init();
    }

    QmlSharedPointer<T, B>& operator=(const QmlSharedPointer<T, B>& d)
    {
        deinit();
        QSharedPointer<T>::operator=(d);
        init();
        return *this;
    }

    // The MOC doesn't generate this for us anymore
    const QMetaObject *metaObject() const
    {
        return &staticMetaObject;
    }

    void *qt_metacast(const char *_clname)
    {
        //qDebug() << "Attempted metacast";
        return nullptr; // disable casting
    }

    int qt_metacall(QMetaObject::Call _c, int _id, void **_a)
    {
        //Debug() << "qt_metacall" << _c << _id;
        return dynamic_metacall(this, _c, _id, _a);
    }
};

//template <typename T, typename B>
//typename std::enable_if<std::is_same<B, QObject>::value, int>::type
//QmlSharedPointer<T, B>::dynamic_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
//{
//    _id = ((QObject *)_o)->qt_metacall(_c, _id, _a);
//    return _id;
//}

//template <typename T, typename B>
//typename std::enable_if<!std::is_same<B, QObject>::value, int>::type
//QmlSharedPointer<T, B>::dynamic_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
//{
//    const int n_methods = staticMetaObject.methodCount() - staticMetaObject.superClass()->methodCount();
//    const int n_properties = staticMetaObject.propertyCount() - staticMetaObject.superClass()->propertyCount();
//    _id = B::dynamic_metacall(_o, _c, _id, _a);
//    if (_id < 0)
//        return _id;
//    if (_c == QMetaObject::InvokeMetaMethod) {
//        if (_id < n_methods)
//            qt_static_metacall(_o, _c, _id, _a);
//        _id -= n_methods;
//    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
//        if (_id < n_methods)
//            *reinterpret_cast<int*>(_a[0]) = -1;
//        _id -= n_methods;
//    }
//    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
//          || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
//        qt_static_metacall(_o, _c, _id, _a);
//        _id -= n_properties;
//    } else if (_c == QMetaObject::QueryPropertyDesignable) {
//        _id -= n_properties;
//    } else if (_c == QMetaObject::QueryPropertyScriptable) {
//        _id -= n_properties;
//    } else if (_c == QMetaObject::QueryPropertyStored) {
//        _id -= n_properties;
//    } else if (_c == QMetaObject::QueryPropertyEditable) {
//        _id -= n_properties;
//    } else if (_c == QMetaObject::QueryPropertyUser) {
//        _id -= n_properties;
//    }
//    return _id;
//}

template <typename T, typename B> void QmlSharedPointer<T, B>::findAndActivateSignal(QObject *_o, int _id, void **_a)
{
    // Find which base class the given signal is for
    auto current_metaobject = &staticMetaObject;
    for (;;) {
        auto super_metaobject = current_metaobject->superClass();
        auto first_child_method = super_metaobject->methodOffset() + super_metaobject->methodCount();
        if (_id >= first_child_method) {
            QMetaObject::activate(_o, current_metaobject, _id - first_child_method, _a);
            break;
        }
        current_metaobject = super_metaobject;
    }
}

template <typename T, typename B> void QmlSharedPointer<T, B>::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QmlSharedPointer<T, B> *>(_o);
    auto *_child = _t->data();
    Q_ASSERT(_child != nullptr);

    qDebug() << "Static metacall on..." << staticMetaObject.className() << _o << _c << _id;

    if (_c == QMetaObject::InvokeMetaMethod) {
        auto newId = _id + staticMetaObject.superClass()->methodCount();

        auto method = QmlSharedPointer<T, B>::staticMetaObject.method(newId);
        auto sig = QMetaObject::normalizedSignature(method.methodSignature());
        if (method.methodType() == QMetaMethod::Signal) {
            QMetaObject::activate(_o, &staticMetaObject, _id, _a);
        } else {
            _child->qt_metacall(_c, newId, _a);
        }
    } else if (_c == QMetaObject::IndexOfMethod ||
               _c == QMetaObject::ReadProperty ||
               _c == QMetaObject::WriteProperty ||
               _c == QMetaObject::ResetProperty) {
        auto newId = _id + QObject::staticMetaObject.propertyCount();
        _child->qt_metacall(_c, newId, _a);
    } else {
        Q_ASSERT(false); // Unhandled request
    }
}

template<typename T, typename B>
const QMetaObject *QmlSharedPointer<T, B>::gen_superdata()
{
    //return T::staticMetaObject.d.superdata;
    return &B::staticMetaObject;
    //return &QmlSharedPointer<B, B>::staticMetaObject;
}

template<typename T, typename B>
const QByteArrayData *QmlSharedPointer<T, B>::gen_stringdata()
{
    // The MOC always places the strings right after the QByteArrayDatas,
    // so we can back out the number of strings based on the first offset
    int n_strings = T::staticMetaObject.d.stringdata[0].offset / sizeof (T::staticMetaObject.d.stringdata[0]);

    // Copy the child's string data
    // (copy the lookup table, but don't copy the actual strings.
    // Just point the new lookup table at the old strings)
    const int MAX_N_STRINGS = 128;
    Q_ASSERT(n_strings <= MAX_N_STRINGS);
    static QByteArrayData new_stringdata[MAX_N_STRINGS];

    for (int i=0; i<MAX_N_STRINGS; i++) {
        new_stringdata[i].ref.atomic.store(-1); // Don't attempt to free
    }

    for (int i=0; i<n_strings; i++) {
        new_stringdata[i].size = T::staticMetaObject.d.stringdata[i].size;
        new_stringdata[i].offset = T::staticMetaObject.d.stringdata[i].offset + ((qptrdiff)&(T::staticMetaObject.d.stringdata[i]) - (qptrdiff)&new_stringdata[i]);
    }

    // Override the first string, which is the name:
    const int MAX_N_CHARS = 128;
    static char new_name[MAX_N_CHARS]{};
    strcpy(new_name, "QmlSharedPointer<");
    strncat(new_name, T::staticMetaObject.className(), 127);
    strncat(new_name, ">", 127);
    new_stringdata[0].size = strlen(new_name);
    new_stringdata[0].offset = ((qptrdiff)&new_name - (qptrdiff)&new_stringdata[0]);

    //const QByteArrayDataPtr first = { const_cast<QByteArrayData*>(&new_stringdata[0]) };
    //qDebug() << "new_stringdata[0]" << (QByteArray)first;
 
    return new_stringdata;
}

template<typename T, typename B>
const uint *QmlSharedPointer<T, B>::gen_data()
{
    return T::staticMetaObject.d.data;
}

template<typename T, typename B>
const QMetaObject * const *QmlSharedPointer<T, B>::gen_relatedMetaObjects()
{
    return T::staticMetaObject.d.relatedMetaObjects;
}

template<typename T, typename B>
void *QmlSharedPointer<T, B>::gen_extradata()
{
    return T::staticMetaObject.d.extradata;
}

QT_INIT_METAOBJECT template<typename T, typename B> const QMetaObject QmlSharedPointer<T, B>::staticMetaObject = { {
    QmlSharedPointer<T, B>::gen_superdata(),
    QmlSharedPointer<T, B>::gen_stringdata(),
    QmlSharedPointer<T, B>::gen_data(),
    QmlSharedPointer<T, B>::qt_static_metacall,
    QmlSharedPointer<T, B>::gen_relatedMetaObjects(),
    QmlSharedPointer<T, B>::gen_extradata(),
} };
