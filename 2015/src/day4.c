#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <time.h>
#include "misc.h"

#define DIGITS(v) (sizeof(v) * CHAR_BIT * 28 / 93 + 1)

int part1(char *input);
int part2(char *input);

int main(void)
{
        char input[40] = "ckczppom";
        part1(input);
        part2(input);
        return 0;
}

int
part1(char *input)
{
        EVP_MD_CTX *mdctx;
        const EVP_MD *md;
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;

        char md_buffer_five_zeros[100] = {0};

        char *five_ptr = md_buffer_five_zeros;

        int five_count = 0;

        md = EVP_get_digestbyname("MD5");
        if (md == NULL) {
                printf("Unkown message digest\n");
                exit(1);
        }

        mdctx = EVP_MD_CTX_new();

        for (u32 i = 0;; i++) {
                if (!EVP_DigestInit_ex(mdctx, md, NULL)) {
                        printf("Message digest initialization failed.\n");
                        EVP_MD_CTX_free(mdctx);
                        exit(1);
                }

                if (!EVP_DigestUpdate(mdctx, input, strlen(input))) {
                    printf("Message digest update failed.\n");
                    EVP_MD_CTX_free(mdctx);
                    exit(1);
                }

                if (!EVP_DigestFinal(mdctx, md_value, &md_len)) {
                    printf("Message digest finalization failed.\n");
                    EVP_MD_CTX_free(mdctx);
                    exit(1);
                }

                // print md_value[j] in buffer and then check if the first 5 hexas are 0
                for (u32 j = 0; j < 5; j++) {
                        sprintf(five_ptr,"%02x", md_value[j]);
                        five_ptr += 2;
                }
                for (int j = 0; j < 5; j++) {
                        if (md_buffer_five_zeros[j] == '0') {
                                five_count++;
                        }
                }
                if (five_count == 5) {
                        printf("i = %d\n", i-1);
                        break;
                }
                five_ptr = &md_buffer_five_zeros[0];
                five_count = 0;

                char digit_buf[DIGITS(i) + 1];
                sprintf(digit_buf, "%u", i);
                strcpy(&input[8], digit_buf);

                EVP_MD_CTX_reset(mdctx);
        }
        EVP_MD_CTX_free(mdctx);
        return 0;

}

int
part2(char *input)
{
        EVP_MD_CTX *mdctx;
        const EVP_MD *md;
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int md_len;

        char md_buffer_six_zeros[10] = {0};
        char *six_ptr = md_buffer_six_zeros;

        int six_count = 0;

        md = EVP_get_digestbyname("MD5");
        if (md == NULL) {
                printf("Unkown message digest\n");
                exit(1);
        }

        mdctx = EVP_MD_CTX_new();

        for (u32 i = 0;; i++) {
                if (!EVP_DigestInit_ex(mdctx, md, NULL)) {
                        printf("Message digest initialization failed.\n");
                        EVP_MD_CTX_free(mdctx);
                        exit(1);
                }

                if (!EVP_DigestUpdate(mdctx, input, strlen(input))) {
                    printf("Message digest update failed.\n");
                    EVP_MD_CTX_free(mdctx);
                    exit(1);
                }

                if (!EVP_DigestFinal(mdctx, md_value, &md_len)) {
                    printf("Message digest finalization failed.\n");
                    EVP_MD_CTX_free(mdctx);
                    exit(1);
                }


                // print md_value[j] to buffer and checks if the first 6 hexas are 0
                for (u32 j = 0; j < 6; j++) {
                        sprintf(six_ptr,"%02x", md_value[j]);
                        six_ptr += 2;
                }

                for (int j = 0; j < 6; j++) {
                        if (md_buffer_six_zeros[j] == '0') {
                                six_count++;
                        }
                }
                if (six_count == 6) {
                        printf("i = %d\n", i-1);
                        break;
                }
                six_ptr = &md_buffer_six_zeros[0];
                six_count = 0;

                char digit_buf[DIGITS(i) + 1];
                sprintf(digit_buf, "%u", i);
                strcpy(&input[8], digit_buf);

                EVP_MD_CTX_reset(mdctx);
        }
        EVP_MD_CTX_free(mdctx);
        return 0;
}
