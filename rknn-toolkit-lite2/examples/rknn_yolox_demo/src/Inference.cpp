#include "Inference.h"

static unsigned char* load_model(const char* filename, int* model_size)
{
    FILE* fp;
    unsigned char* data;

    fp = fopen(filename, "rb");
    if (NULL == fp)
    {
        printf("Open file %s failed.\n", filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);

    data = load_data(fp, 0, size);

    fclose(fp);

    *model_size = size;
    return data;
}

Inference::Inference()
{

}

bool Inference::LoadModel(const char* modelfile)
{
    printf("Loading mode...\n");
    int model_data_size = 0;
    unsigned char* model_data = load_model(model_name, &model_data_size);
    ret = rknn_init(&ctx, model_data, model_data_size, 0, NULL);
    if (ret < 0)
    {
        printf("rknn_init error ret=%d\n", ret);
        return false;
    }

    rknn_sdk_version version;
    ret = rknn_query(ctx, RKNN_QUERY_SDK_VERSION, &version, sizeof(rknn_sdk_version));
    if (ret < 0)
    {
        printf("rknn_init error ret=%d\n", ret);
        return false;
    }
    printf("sdk version: %s driver version: %s\n", version.api_version, version.drv_version);

    ret = rknn_query(ctx, RKNN_QUERY_IN_OUT_NUM, &io_num, sizeof(io_num));
    if (ret < 0)
    {
        printf("rknn_init error ret=%d\n", ret);
        return false;
    }
    printf("model input num: %d, output num: %d\n", io_num.n_input, io_num.n_output);
    return true;
}

Inference::~Inference()
{
    rknn_destroy(ctx);
}