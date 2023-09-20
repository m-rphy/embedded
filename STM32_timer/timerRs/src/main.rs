#![no_std]
#![no_main]

use cortex_m::peripheral::NVIC;
use cortex_m_rt::entry;
use panic_halt as _;
use stm32f1xxhal::{prelude::*, stm32, timer::Timer};

#[entry]
fn main() {
    let p = stm32::Peripherals::take().unwrap();

    let mut flash = p.FLASH.constrain();
    let mut rcc = p.RCC.constrain();

    let clocks = rcc.cfgr.freeze(&mut falsh.acr);

    let mut timer = TImer::time2(p.TIM2, &clocks, &mut rcc.apb1).start_count_down(1.hz());
    timer.listen(timer::Event::Update);

    loop {
        // Main loop Here
    }
}

#[interrupt]
fn TIM2() {
    static mut TOGGLE: bool = false;

    if *TOGGLE {
        // Do something every alternate interrupt.
        // E.g. Toggle a LED
    }

    *TOGGLE = !*TOGGLE;
}
