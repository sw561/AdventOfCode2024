


# Actual solution for adding numbers...



x0 x1 x2 x3 ...
y0 y1 y2 y3 ...

z0 = x0 ^ y0

carry bit = x0 & y0

then...

z1 = x1 ^ y1 ^ carry_bit


    if no carry_bit

            x1:
            0 1          new_carry_bit = x1 & y1
       y1 0 0 1            0 0
          1 1 0            0 1

    elif carry_bit

            x1:         new_carry_bit = (carry_bit & (x1 | y1)) | (x1 & y1)
            0 1                         (carry_bit & (x1 ^ y1)) | (x1 & y1)
       y1 0 1 0            0 1
          1 0 1            1 1



z01 = bhq ^ kvj
    = (x01 ^ y01 ^ kvj) # kvj is old carry bit x00 & y00


htw = rtg | wkc
    = (x01 & y01) | wkc
    = (x01 & y01) | (kvj & bhq)
    = (x01 & y01) | (kvj & (x01 ^ y01))


z02 = mpj ^ htw
    = x02 ^ y02 ^ htw # htw is new carry bit

.....


# First swap vcf <-> z10

Now look at z16
z16 = dcj ^ rfv
    = (x16 ^ y16) ^ rfv

New carry bit
jjf = dpc | pwj
    = (dcj & rfv) | (x16 & y16)
    = ((x16 ^ y16) & rfv) | (x16 & y16)


z17 = qjg & jjf
    = (x17 ^ y17) & jjf

# second swap fhg <-> z17

z34 = qnv ^ vbh
    = qnv ^ (x34 ^ y34)

new carry bit

jsn = tgn | bbf
    = (qnv & vbh) | bbg
    = (qnv & (x34 ^ y34)) | (x34 & y34)

z35 = dvb ^ jsn
    = (x35 & y35) ^ jsn

should be x35 ^ y35 ^ jsn

    fsq = x35 ^ y35

# third swap fsq <-> dvb

z39 = rvd | wrj

kmg = x39 ^ y39

# fourth swap z39 <-> tnc


dvb,fhg,fsq,tnc,vcf,z10,z17,z39
