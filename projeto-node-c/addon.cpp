#include <node.h>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::String;
using v8::Local;
using v8::Number;
using v8::Exception;
using v8::Value;

void Hello(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(
        isolate, "hello world").ToLocalChecked());
}

void Add(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if(args.Length() < 2) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()
        ));
        return;
    }

    if(!args[0]->IsNumber() || !args[1]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()
        ));
        return;
    }

    double value = args[0].As<Number>()->Value() + args[1].As<Number>()->Value();
    Local<Number> num = Number::New(isolate, value);

    args.GetReturnValue().Set(num);
}


void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "hello", Hello);
    NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(addon, Initialize)