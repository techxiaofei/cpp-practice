class String{
public:
    String(const char* str = "");
    String(const String& other);
    ~String();
    String& operator=(const String& other);

public:
    char* str_;
};