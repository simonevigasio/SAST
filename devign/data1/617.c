void op_cp1_registers(void)

{

    if (!(env->CP0_Status & (1 << CP0St_FR)) && (PARAM1 & 1)) {

        CALL_FROM_TB1(do_raise_exception, EXCP_RI);

    }

    RETURN();

}
