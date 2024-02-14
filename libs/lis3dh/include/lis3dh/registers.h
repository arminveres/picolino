#ifndef LIS3DH_H_
#define LIS3DH_H_

#include <cstdint>

namespace lis3dh {
// namespace regs {
struct regs {
    static constexpr uint8_t WHO_AM_I = 0b00110011;

    static constexpr uint8_t REG_STATUS_AUX = 0x07;
    static constexpr uint8_t REG_OUT_ADC1_L = 0x08;
    static constexpr uint8_t REG_OUT_ADC1_H = 0x09;
    static constexpr uint8_t REG_OUT_ADC2_L = 0x0a;
    static constexpr uint8_t REG_OUT_ADC2_H = 0x0b;
    static constexpr uint8_t REG_OUT_ADC3_L = 0x0c;
    static constexpr uint8_t REG_OUT_ADC3_H = 0x0d;
    static constexpr uint8_t REG_INT_COUNTER_REG = 0x0e;

    // Device ID
    static constexpr uint8_t REG_WHO_AM_I = 0x0F;
    static constexpr uint8_t REG_TEMP_CFG_REG = 0x1f;
    static constexpr uint8_t REG_CTRL_REG1 = 0x20;
    static constexpr uint8_t REG_CTRL_REG2 = 0x21;
    static constexpr uint8_t REG_CTRL_REG3 = 0x22;
    static constexpr uint8_t REG_CTRL_REG4 = 0x23;
    static constexpr uint8_t REG_CTRL_REG5 = 0x24;
    static constexpr uint8_t REG_CTRL_REG6 = 0x25;
    static constexpr uint8_t REG_REFERENCE = 0x26;
    static constexpr uint8_t REG_STATUS_REG = 0x27;
    static constexpr uint8_t REG_OUT_X_L = 0x28;
    static constexpr uint8_t REG_OUT_X_H = 0x29;
    static constexpr uint8_t REG_OUT_Y_L = 0x2a;
    static constexpr uint8_t REG_OUT_Y_H = 0x2b;
    static constexpr uint8_t REG_OUT_Z_L = 0x2c;
    static constexpr uint8_t REG_OUT_Z_H = 0x2d;
    static constexpr uint8_t REG_FIFO_CTRL_REG = 0x2e;
    static constexpr uint8_t REG_FIFO_SRC_REG = 0x2f;
    static constexpr uint8_t REG_INT1_CFG = 0x30;
    static constexpr uint8_t REG_INT1_SRC = 0x31;
    static constexpr uint8_t REG_INT1_THS = 0x32;
    static constexpr uint8_t REG_INT1_DURATION = 0x33;
    static constexpr uint8_t REG_CLICK_CFG = 0x38;
    static constexpr uint8_t REG_CLICK_SRC = 0x39;
    static constexpr uint8_t REG_CLICK_THS = 0x3a;
    static constexpr uint8_t REG_TIME_LIMIT = 0x3b;
    static constexpr uint8_t REG_TIME_LATENCY = 0x3c;
    static constexpr uint8_t REG_TIME_WINDOW = 0x3d;

    static constexpr uint8_t STATUS_ZYXOR = 0x80;
    static constexpr uint8_t STATUS_ZOR = 0x40;
    static constexpr uint8_t STATUS_YOR = 0x20;
    static constexpr uint8_t STATUS_XOR = 0x10;
    static constexpr uint8_t STATUS_ZYXDA = 0x08;
    static constexpr uint8_t STATUS_ZDA = 0x04;
    static constexpr uint8_t STATUS_YDA = 0x02;
    static constexpr uint8_t STATUS_XDA = 0x01;

    static constexpr uint8_t STATUS_AUX_321OR = 0x80;
    static constexpr uint8_t STATUS_AUX_3OR = 0x40;
    static constexpr uint8_t STATUS_AUX_2OR = 0x20;
    static constexpr uint8_t STATUS_AUX_1OR = 0x10;
    static constexpr uint8_t STATUS_AUX_321DA = 0x08;
    static constexpr uint8_t STATUS_AUX_3DA = 0x04;
    static constexpr uint8_t STATUS_AUX_2DA = 0x02;
    static constexpr uint8_t STATUS_AUX_1DA = 0x01;

    static constexpr uint8_t CTRL_REG1_ODR3 = 0x80;
    static constexpr uint8_t CTRL_REG1_ODR2 = 0x40;
    static constexpr uint8_t CTRL_REG1_ODR1 = 0x20;
    static constexpr uint8_t CTRL_REG1_ODR0 = 0x10;
    static constexpr uint8_t CTRL_REG1_LPEN = 0x08;
    static constexpr uint8_t CTRL_REG1_ZEN = 0x04;
    static constexpr uint8_t CTRL_REG1_YEN = 0x02;
    static constexpr uint8_t CTRL_REG1_XEN = 0x01;

    static constexpr uint8_t RATE_1_HZ = 0x10;
    static constexpr uint8_t RATE_10_HZ = 0x20;
    static constexpr uint8_t RATE_25_HZ = 0x30;
    static constexpr uint8_t RATE_50_HZ = 0x40;
    static constexpr uint8_t RATE_100_HZ = 0x50;
    static constexpr uint8_t RATE_200_HZ = 0x60;
    static constexpr uint8_t RATE_400_HZ = 0x70;

    static constexpr uint8_t CTRL_REG2_HPM1 = 0x80;
    static constexpr uint8_t CTRL_REG2_HPM0 = 0x40;
    static constexpr uint8_t CTRL_REG2_HPCF2 = 0x20;
    static constexpr uint8_t CTRL_REG2_HPCF1 = 0x10;
    static constexpr uint8_t CTRL_REG2_FDS = 0x08;
    static constexpr uint8_t CTRL_REG2_HPCLICK = 0x04;
    static constexpr uint8_t CTRL_REG2_HPIS2 = 0x02;
    static constexpr uint8_t CTRL_REG2_HPIS1 = 0x01;

    static constexpr uint8_t CTRL_REG3_I1_CLICK = 0x80;
    static constexpr uint8_t CTRL_REG3_I1_INT1 = 0x40;
    static constexpr uint8_t CTRL_REG3_I1_DRDY = 0x10;
    static constexpr uint8_t CTRL_REG3_I1_WTM = 0x04;
    static constexpr uint8_t CTRL_REG3_I1_OVERRUN = 0x02;

    static constexpr uint8_t CTRL_REG4_BDU = 0x80;
    static constexpr uint8_t CTRL_REG4_BLE = 0x40;
    static constexpr uint8_t CTRL_REG4_FS1 = 0x20;
    static constexpr uint8_t CTRL_REG4_FS0 = 0x10;
    static constexpr uint8_t CTRL_REG4_HR = 0x08;
    static constexpr uint8_t CTRL_REG4_ST1 = 0x04;
    static constexpr uint8_t CTRL_REG4_ST0 = 0x02;
    static constexpr uint8_t CTRL_REG4_SIM = 0x01;

    static constexpr uint8_t CTRL_REG5_BOOT = 0x80;
    static constexpr uint8_t CTRL_REG5_FIFO_EN = 0x40;
    static constexpr uint8_t CTRL_REG5_LIR_INT1 = 0x08;
    static constexpr uint8_t CTRL_REG5_D4D_INT1 = 0x04;

    static constexpr uint8_t CTRL_REG6_I2_CLICK = 0x80;
    static constexpr uint8_t CTRL_REG6_I2_INT2 = 0x40;
    static constexpr uint8_t CTRL_REG6_BOOT_I2 = 0x10;
    static constexpr uint8_t CTRL_REG6_H_LACTIVE = 0x02;

    static constexpr uint8_t INT1_CFG_AOI = 0x80;
    static constexpr uint8_t INT1_CFG_6D = 0x40;
    static constexpr uint8_t INT1_CFG_ZHIE_ZUPE = 0x20;
    static constexpr uint8_t INT1_CFG_ZLIE_ZDOWNE = 0x10;
    static constexpr uint8_t INT1_CFG_YHIE_YUPE = 0x08;
    static constexpr uint8_t INT1_CFG_YLIE_YDOWNE = 0x04;
    static constexpr uint8_t INT1_CFG_XHIE_XUPE = 0x02;
    static constexpr uint8_t INT1_CFG_XLIE_XDOWNE = 0x01;

    static constexpr uint8_t INT1_SRC_IA = 0x40;
    static constexpr uint8_t INT1_SRC_ZH = 0x20;
    static constexpr uint8_t INT1_SRC_ZL = 0x10;
    static constexpr uint8_t INT1_SRC_YH = 0x08;
    static constexpr uint8_t INT1_SRC_YL = 0x04;
    static constexpr uint8_t INT1_SRC_XH = 0x02;
    static constexpr uint8_t INT1_SRC_XL = 0x01;

    static constexpr uint8_t TEMP_CFG_ADC_PD = 0x80;
    static constexpr uint8_t TEMP_CFG_TEMP_EN = 0x40;

    static constexpr uint8_t FIFO_CTRL_BYPASS = 0x00;
    static constexpr uint8_t FIFO_CTRL_FIFO = 0x40;
    static constexpr uint8_t FIFO_CTRL_STREAM = 0x80;
    static constexpr uint8_t FIFO_CTRL_STREAM_TO_FIFO = 0xc0;

    static constexpr uint8_t FIFO_SRC_WTM = 0x80;
    static constexpr uint8_t FIFO_SRC_OVRN = 0x40;
    static constexpr uint8_t FIFO_SRC_EMPTY = 0x20;
    static constexpr uint8_t FIFO_SRC_FSS_MASK = 0x1f;
};
}  // namespace lis3dh
#endif  // !LIS3DH_H_
