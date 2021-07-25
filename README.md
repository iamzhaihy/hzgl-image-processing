#   O p e n G L   I m a g e   P r o c e s s i n g   T e s t b e n c h  
  
 H o n g y u   Z H A I   ( [ G i t h u b ] ( h t t p s : / / g i t h u b . c o m / i a m z h a i h y ) ,   [ L i n k e d I n ] ( h t t p s : / / w w w . l i n k e d i n . c o m / i n / h o n g y u - z h a i - 3 4 b 9 6 1 1 3 9 / ) )  
  
 ! [ M a i n   U I ] ( . / r e s u l t s / m a i n - u i . p n g )  
  
 # #   A b o u t   t h i s   P r o j e c t  
  
 T o   m e ,   G P U - a c c e l e r a t e d   i m a g e   p r o c e s s i n g   i s   v e r y   i n t e r e s t i n g .   T h e   b o i l e r p l a t e   c o d e ,   o n   t h e   o t h e r   h a n d ,   i s   n o   f u n   t o   w r i t e .   T o   e n a b l e   f a s t e r   d e v e l o p m e n t ,   I   w r o t e   m y s e l f   a   s m a l l   t o o l k i t   a n d   u s e d   i t   t o   m a k e   t h i s   i m a g e   p r o c e s s i n g   t e s t b e n c h .   I t   i s   e a s y   t o   s w i t c h   b e t w e e n   i m a g e s ,   e f f e c t s ,   a n d   c o n v o l u t i o n   k e r n e l s .    
  
 T h i s   i s   t h e   s i b l i n g   p r o j e c t   o f   h t t p s : / / g i t h u b . c o m / i a m z h a i h y / h z g l - o b j - v i e w e r .  
  
 # #   C o m p i l e   a n d   R u n  
  
 B e f o r e   y o u   s t a r t ,   m a k e   s u r e   y o u   h a v e   t h e   f o l l o w i n g   t h i n g s :  
  
 -   C M a k e   3 . 1 5 +  
 -   A   C + +   c o m p i l e r   f o r   y o u r   p l a t f o r m  
 -   H a r d w a r e   t h a t   s u p p o r t s   m o d e r n   O p e n G L  
  
 T o   r u n   t h e   p r o g r a m   y o u r s e l f ,   t y p e   t h e   f o l l o w i n g   c o m m a n d s  
  
 ` ` ` b a s h  
 g i t   c l o n e   - - r e c u r s i v e   h t t p s : / / g i t h u b . c o m / i a m z h a i h y / h z g l - o b j - v i e w e r . g i t  
 c d   h z g l - o b j - v i e w e r  
 m k d i r   b u i l d   & &   c d   b u i l d  
 c m a k e   . .  
 c m a k e   - - b u i l d   .  
 ` ` `  
  
 T h e   e x t e r n a l   l i b r a r i e s   a r e   a l l   c o m p i l e d   s t a t i c a l l y ,   w h i c h   m e a n s   i t   s h o u l d   w o r k   o u t   o f   t h e   b o x   i f   y o u   h a v e   t h e   t h i n g s   a b o v e .  
  
 # #   B a s i c   C o n t r o l s  
  
 U s i n g   t h e   G U I ,   t h e   u s e r   c a n :  
  
 -   S w i t c h   b e t w e e n   a v a i l a b l e   i m a g e s   b y   c l i c k i n g   o n   a n   i t e m   i n   t h e   " I m a g e s "   l i s t  
 -   S w i t c h   b e t w e e n   s h a d e r   p r o g r a m s   b y   c l i c k i n g   o n   a n   i t e m   i n   t h e   " E f f e c t s "   l i s t  
     -   C h o o s e   t h e   k e r n e l   i f   " C o n v o l u t i o n "   h a s   b e e n   s e l e c t e d  
     -   T w e a k   t h e   3   b y   3   k e r n e l s   v i a   t h e   w i d g e t s   i n   t h e   b o t t o m  
  
 S e v e r a l   k e y b o a r d   s h o r t c u t s   a r e   p r o v i d e d :  
  
 -   P r e s s   ` Q `   o r   ` E s c a p e `   t o   q u i t   t h e   p r o g r a m  
 -   P r e s s   ` F `   o r   ` P r i n t S c r e e n `   t o   t a k e   a   s c r e e n s h o t   ( w i l l   b e   s t o r e d   i n   t h e   s a m e   d i r e c t o r y   a s   t h e   e x e c u t a b l e )  
  
 # #   I m p l e m e n t e d   F i l t e r s  
  
 * * P a s s t h r o u g h   ( i d e n t i t y ) * *  
  
 ! [ i d e n t i t y ] ( . / r e s u l t s / f l o w e r - p a s s t h r o u g h . p n g )  
  
 * * G r e y s c a l e   * *  
  
 ! [ g r e y s c a l e ] ( . / r e s u l t s / f l o w e r - g r e y s c a l e . p n g )  
  
 * * C o n v o l u t i o n   ( E m b o s s ) * *  
  
 ! [ e m b o s s ] ( . / r e s u l t s / f l o w e r - e m b o s s . p n g )  
  
 * * C o n v o l u t i o n   ( O u t l i n e ) * *  
  
 ! [ o u t l i n e ] ( . / r e s u l t s / f l o w e r - o u t l i n e . p n g )  
  
 * * C o n v o l u t i o n   ( S h a r p e n ) * *  
  
 ! [ s h a r p e n ] ( . / r e s u l t s / f l o w e r - s h a r p e n . p n g )  
  
 * * C o n v o l u t i o n   ( T r i a n g l e   B l u r ) * *  
  
 ! [ t r i - b l u r ] ( . / r e s u l t s / f l o w e r - t r i - b l u r . p n g )  
  
 * * C o n v o l u t i o n   ( S o b e l   H o r i z o n t a l ) * *  
  
 ! [ s o b e l   h ] ( . / r e s u l t s / f l o w e r - s o b e l - h o r i z o n t a l . p n g )  
  
 * * C o n v o l u t i o n   ( S o b e l   V e r t i c a l ) * *  
  
 ! [ s o b e l   v ] ( . / r e s u l t s / f l o w e r - s o b e l - v e r t i c a l . p n g )  
  
 * * C o n v o l u t i o n   ( P r e w i t t     H o r i z o n t a l ) * *  
  
 ! [ p r e w i t t   h ] ( . / r e s u l t s / f l o w e r - p r e w i t t - h o r i z o n t a l . p n g )  
  
 * * C o n v o l u t i o n   ( P r e w i t t   V e r t i c a l ) * *  
  
 ! [ p r e w i t t   v ] ( . / r e s u l t s / f l o w e r - p r e w i t t - v e r t i c a l . p n g )  
  
  
  
 # #   F u t u r e   P l a n s   f o r   t h e   P r o j e c t  
  
 H e r e   i s   m y   p l a n   f o r   t h e   f u t u r e   i m p r o v e m e n t  
  
 -   M o r e   f l e x i b l e   w i n d o w   s e t t i n g s  
     -   C o r r e c t l y   h a n d l e   w i n d o w   r e s i z i n g  
 -   T e x t u r e   f i l t e r i n g   r e l a t e d  
     -   A d j u s t   f i l t e r i n g   m e t h o d   t o   m a k e   k e r n e l s   w o r k   b e t t e r   o n   h i g h   r e s o l u t i o n   p i c t u r e s  
 -   B i g g e r   a n d   m o r e   c o m p l e x   k e r n e l s  
     -   G a u s s i a n   B l u r  
     -   L a p l a c i a n   o f   G a u s s i a n  
 -   I m p r o v e   i n t e r a c t i v e   U I  
     -   L o a d   i m a g e   f i l e   f r o m   a   d r o p d o w n   f i l e   m e n u  
     -   A l l o w   t h e   u s e r   t o   a p p l y   m u l t i p l e   e f f e c t   a t   t h e   s a m e   t i m e  
     -   A d d   a   s i m p l e   e d i t o r   t h a t   r e c o m p i l e s   s h a d e r s   a f t e r   t h e   u s e r   s a v e s   c h a n g e s  
 