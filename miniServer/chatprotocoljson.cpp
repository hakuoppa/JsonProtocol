#include "chatprotocoljson.h"

QJsonObject ChatProtocolJson::textMessage(QString message, QString receiver) {
    QJsonObject json;
    json["type"] = "Text";
    json["message"] = message;
    json["receiver"] = receiver;
    return json;
}

// Implement similar functions for other message types...

void ChatProtocolJson::loadData(const QJsonObject &json) {
    QString typeString = json["type"].toString();
    if (typeString == "Text") {
        _type = Text;
        _message = json["message"].toString();
        _receiver = json["receiver"].toString();
    }
    // Implement similar parsing logic for other message types...
}
