#pragma once

#include <QSharedPointer>

template <class T>
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
            QMetaObject::connect(QmlSharedPointer<T>::data(), i, this, i);
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
            QMetaObject::disconnect(QmlSharedPointer<T>::data(), i, this, i);
        }
    }
    static const QMetaObject *gen_superdata();
    static const QByteArrayData *gen_stringdata();
    static const uint *gen_data();
    static const QMetaObject * const *gen_relatedMetaObjects();
    static void *gen_extradata();

public:
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

    QmlSharedPointer(const QmlSharedPointer<T> &other)
        : QSharedPointer<T>(other)
    {
        init();
    }

    QmlSharedPointer(const QWeakPointer<T> &other)
        : QSharedPointer<T>(other)
    {
        init();
    }

    QmlSharedPointer<T>& operator=(const QmlSharedPointer<T>& d)
    {
        deinit();
        QSharedPointer<T>::operator=(d);
        init();
        return *this;
    }

//    virtual const QMetaObject *metaObject() const
//    {
        // This is sketchy but it works, and might be less sketchy than using QMetaObjectBuilder
        //return QmlSharedPointer<T>::data()->metaObject();

//QT_INIT_METAOBJECT const QMetaObject ExampleQmlObject::staticMetaObject = { {
//    &QObject::staticMetaObject,
//    qt_meta_stringdata_ExampleQmlObject.data,
//    qt_meta_data_ExampleQmlObject,
//    qt_static_metacall,
//    nullptr,
//    nullptr
//} };
//        return &childMetaObject;
//    }

    //Virtual void *qt_metacast(const char *)
    //{
    //    qDebug() << "META-CAST????";
    //    // Disable casting
    //    Q_ASSERT(false);
    //    return nullptr;
    //}
};

struct qt_meta_stringdata_QmlSharedPointer_t {
    QByteArrayData data[1];
};

//template<typename T>
//void QmlSharedPointer<T>::qt_static_metacall(QMetaObject::Call _c, int _id, void** _a)
//{
//    qDebug() << "meta-call!" << _c;
//    //return QmlSharedPointer<T>::data()->qt_metacall(_c, _id, _a); // Dangerous??
//    //Q_ASSERT(false);
//    //return -1;
//    if (_c == QMetaObject::InvokeMetaMethod) {
//        auto method = metaObject()->method(_id);
//        auto sig = QMetaObject::normalizedSignature(method.methodSignature());
//        qDebug() << "Invoke method" << sig;
//        if (method.methodType() == QMetaMethod::Signal) {
//            auto newId = _id - QObject::staticMetaObject.methodCount();
//            QMetaObject::activate(this, metaObject(), newId, _a);
//            return -1;
//        } else {
//            if (_id < QObject::staticMetaObject.methodCount()) {
//                // Handle things like deleteLater internally
//                return QObject::qt_metacall(_c, _id, _a);
//            } else {
//                // Forward on anything else
//                return QmlSharedPointer<T>::data()->qt_metacall(_c, _id, _a); // This could be dangerous as _id might not be the same, but it appears to be the same so :shrug:
//            }
//        }
//    } else if (_c == QMetaObject::IndexOfMethod ||
//               _c == QMetaObject::ReadProperty || 
//               _c == QMetaObject::WriteProperty ||
//               _c == QMetaObject::ResetProperty) {
//        qDebug() << "Property access!" << _c << _id;
//        return QmlSharedPointer<T>::data()->qt_metacall(_c, _id, _a); // This could be dangerous as _id might not be the same
//    } else {
//        qDebug() << "O no!" << _c << _id;
//        return -1;
//    }
//}

// This method gets run before main()
// and is very limited in what it can do,
// hence the old-school C string manipulation
template <typename T>
static const char *get_class_name_string() {
    static char c[128]{};
    strcpy(c, "QmlSharedPointer<");
    strncat(c, T::staticMetaObject.className(), 127);
    strncat(c, ">", 127);
    return c;
}

template <typename T> 
static const char *class_name_string = get_class_name_string<T>();

#define QT_MOC_LITERAL(idx, ptr, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(qintptr(ptr) - qintptr(&qt_meta_stringdata_QmlSharedPointer<T>) \
        - idx * sizeof(QByteArrayData)) \
    )
template <typename T> static const qt_meta_stringdata_QmlSharedPointer_t qt_meta_stringdata_QmlSharedPointer = {
    {
        QT_MOC_LITERAL(0, class_name_string<T>, (int)strlen(class_name_string<T>)), // "QmlSharedPointer<ExampleQmlObject>"
    }
    //"QmlSharedPointer<" + T::staticMetaObject.className() + ">\0"
};

#undef QT_MOC_LITERAL

static const uint qt_meta_data_QmlSharedPointer[] = {
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       //6,   14, // methods
       //2,   62, // properties
       //0,    0, // enums/sets
       //0,    0, // constructors
       //0,       // flags
       //3,       // signalCount
};

//template <typename T> void QmlSharedPointer<T>::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
//{
//    qDebug() << "STATIC METACALL???";
//    return;
//}

template <typename T> void QmlSharedPointer<T>::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    qDebug() << "METACALL";
    auto *_t = static_cast<QmlSharedPointer<T> *>(_o);
    auto *_child = _t->data();
    Q_ASSERT(_child != nullptr);
    //T::staticMetaObject.d.static_metacall(_child, _c, _id, _a);

    //return QmlSharedPointer<T>::data()->qt_metacall(_c, _id, _a); // Dangerous??
    //Q_ASSERT(false);
    //return -1;
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto method = QmlSharedPointer<T>::staticMetaObject.method(_id);
        auto sig = QMetaObject::normalizedSignature(method.methodSignature());
        qDebug() << "Invoke method" << sig;
        if (method.methodType() == QMetaMethod::Signal) {
            auto newId = _id - QObject::staticMetaObject.methodCount();
            QMetaObject::activate(_o, &staticMetaObject, newId, _a);
            //return -1;
        } else {
            if (_id < QObject::staticMetaObject.methodCount()) {
                // Handle things like deleteLater internally
                //QObject::qt_static_metacall(_o, _c, _id, _a); // XXX
            } else {
                // Forward on anything else
                _child->qt_metacall(_c, _id, _a);
            }
        }
    } else if (_c == QMetaObject::IndexOfMethod ||
               _c == QMetaObject::ReadProperty || 
               _c == QMetaObject::WriteProperty ||
               _c == QMetaObject::ResetProperty) {
        qDebug() << "Property access!" << _c << _id;
        _child->qt_metacall(_c, _id, _a);
    } else {
        qDebug() << "O no!" << _c << _id;
    }
}

//QT_INIT_METAOBJECT template<typename T> const QMetaObject QmlSharedPointer<T>::staticMetaObject{};
//QT_INIT_METAOBJECT template<typename T> const QMetaObject QmlSharedPointer<T>::staticMetaObject = { {
//    &QObject::staticMetaObject,
//    qt_meta_stringdata_QmlSharedPointer<T>.data,
//    qt_meta_data_QmlSharedPointer,
//    qt_static_metacall,
//    nullptr,
//    nullptr
//} };

template<typename T>
const QMetaObject *QmlSharedPointer<T>::gen_superdata()
{
    return T::staticMetaObject.d.superdata;
}

template<typename T>
const QByteArrayData *QmlSharedPointer<T>::gen_stringdata()
{
    int n_strings = T::staticMetaObject.constructorCount()
                  + T::staticMetaObject.classInfoCount()
                  + T::staticMetaObject.enumeratorCount()
                  + T::staticMetaObject.methodCount()
                  + T::staticMetaObject.propertyCount();

    Q_UNUSED(n_strings);

    //const QByteArrayDataPtr data = { const_cast<QByteArrayData*>(&T::staticMetaObject.d.stringdata[index]) };

    const int MAX_N_STRINGS = 128;
    Q_ASSERT(n_strings <= MAX_N_STRINGS);
    static QByteArrayData new_stringdata[MAX_N_STRINGS];

    for (int i=0; i<MAX_N_STRINGS; i++) {
        new_stringdata[i].ref.atomic.store(-1); // Don't attempt to free
    }

    for (int i=0; i<n_strings; i++) {
        //memcpy(&new_stringdata[i], &T::staticMetaObject.d.stringdata[i], sizeof(QByteArrayData));
        //new_stringdata[i] = T::staticMetaObject.d.stringdata[i], sizeof(QByteArrayData);
        new_stringdata[i].size = T::staticMetaObject.d.stringdata[i].size;
        new_stringdata[i].offset = T::staticMetaObject.d.stringdata[i].offset + ((qptrdiff)&(T::staticMetaObject.d.stringdata[i]) - (qptrdiff)&new_stringdata[i]);
        //qDebug() << "old stringdata[i] lives at" << (quintptr)&(T::staticMetaObject.d.stringdata[i]);
        //qDebug() << "new stringdata[i] lives at" << (quintptr)&new_stringdata[i];
        //qDebug() << "Old offset is" << T::staticMetaObject.d.stringdata[i].offset;
        //qDebug() << "New size is" << new_stringdata[i].size << "and new offset is" << new_stringdata[i].offset;
    }

    // Override the first string, which is the name:
    const int MAX_N_CHARS = 128;
    static char new_name[MAX_N_CHARS]{};
    strcpy(new_name, "QmlSharedPointer<");
    strncat(new_name, T::staticMetaObject.className(), 127);
    strncat(new_name, ">", 127);
    new_stringdata[0].size = strlen(new_name);
    new_stringdata[0].offset = ((qptrdiff)&new_name - (qptrdiff)&new_stringdata[0]);

    const QByteArrayDataPtr first = { const_cast<QByteArrayData*>(&new_stringdata[0]) };
    //const QByteArrayDataPtr last = { const_cast<QByteArrayData*>(&new_stringdata[n_strings - 1]) };

    qDebug() << "new_stringdata[0]" << (QByteArray)first;
 
    //quintptr first = (quintptr)QByteArray(first).constData();
    //size_t length = (quintptr)QByteArray(last).constData() - first + QByteArray(first).size() + 1;

    ////auto first_byte = (quintptr)first;
    ////auto last_byte = (quintptr)last;
    ////auto size_last = (quintptr)QByteArray(QByteArrayDataPtr{last}).size();

    ////std::cout << "First string:" << (QByteArray)data;
    //qDebug() << "length" << (quintptr)QByteArray(last).constData() << (quintptr)QByteArray(first).constData();// << last_byte - first_byte;
    ////qDebug() << "last" << size_last;

    //return T::staticMetaObject.d.stringdata;
    return new_stringdata;
}

template<typename T>
const uint *QmlSharedPointer<T>::gen_data()
{
    return T::staticMetaObject.d.data;
}

template<typename T>
const QMetaObject * const *QmlSharedPointer<T>::gen_relatedMetaObjects()
{
    return T::staticMetaObject.d.relatedMetaObjects;
}

template<typename T>
void *QmlSharedPointer<T>::gen_extradata()
{
    return T::staticMetaObject.d.extradata;
}

QT_INIT_METAOBJECT template<typename T> const QMetaObject QmlSharedPointer<T>::staticMetaObject = { {
    QmlSharedPointer<T>::gen_superdata(),
    QmlSharedPointer<T>::gen_stringdata(),
    QmlSharedPointer<T>::gen_data(),
    QmlSharedPointer<T>::qt_static_metacall,
    QmlSharedPointer<T>::gen_relatedMetaObjects(),
    QmlSharedPointer<T>::gen_extradata(),
} };
