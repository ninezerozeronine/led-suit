class LinearMapper {
    public:
        void set_max_value(float max_value);
        float get_value_at(int query_value);
    private:
        float floating_modulo(float input, int max);
        float offset;
        float speed;
        float max_value;
}