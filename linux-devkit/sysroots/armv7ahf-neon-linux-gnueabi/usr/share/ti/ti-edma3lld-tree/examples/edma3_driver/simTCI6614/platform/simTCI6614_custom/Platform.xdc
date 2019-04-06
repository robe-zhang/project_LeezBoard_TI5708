/*!
 * File generated by platform wizard. DO NOT MODIFY
 *
 */

metaonly module Platform inherits xdc.platform.IPlatform {

    config ti.platforms.generic.Platform.Instance CPU =
        ti.platforms.generic.Platform.create("CPU", {
            clockRate:      1200,                                       
            catalogName:    "ti.catalog.c6000",
            deviceName:     "TMS320TCI6614",
            externalMemoryMap: 
           [          
                ["DDR3", 
                     {
                        name: "DDR3",
                        base: 0x80000000,                    
                        len: 0x10000000,                    
                        space: "code/data",
                        access: "RWX",
                     }
                ],
           ],
          l1DMode:"32k",
          l1PMode:"32k",
          l2Mode:"0k",

    });
    
instance :
    
    override config string codeMemory  = "L2SRAM";   
    override config string dataMemory  = "L2SRAM";                                
    override config string stackMemory = "L2SRAM";
    
}