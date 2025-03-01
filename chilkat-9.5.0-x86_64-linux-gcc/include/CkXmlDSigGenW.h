// CkXmlDSigGenW.h: interface for the CkXmlDSigGenW class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat 9.5.0.69

#ifndef _CkXmlDSigGenW_H
#define _CkXmlDSigGenW_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkWideCharBase.h"

class CkStringBuilderW;
class CkBinDataW;
class CkPrivateKeyW;
class CkCertW;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkXmlDSigGenW
class CK_VISIBLE_PUBLIC CkXmlDSigGenW  : public CkWideCharBase
{
    private:
	

	// Don't allow assignment or copying these objects.
	CkXmlDSigGenW(const CkXmlDSigGenW &);
	CkXmlDSigGenW &operator=(const CkXmlDSigGenW &);

    public:
	CkXmlDSigGenW(void);
	virtual ~CkXmlDSigGenW(void);

	static CkXmlDSigGenW *createNew(void);
	

	
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	

	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------
	// A comma-separated list of keywords to specify special behaviors to work around
	// potential oddities or special requirements needed for providing signatures to
	// particular systems. This is an open-ended property where new behaviors can be
	// implemented depending on the needs encountered by Chilkat customers. The
	// possible behaviors are listed below. (At this time, there is only one special
	// behavior.)
	//     ForceAddEnvelopedSignatureTransform The "<Transform
	//     Algorithm="http://www.w3.org/2000/09/xmldsig#enveloped-signature" /> " is
	//     normally only added when the Signature is contained within the XML fragment that
	//     is signed. The meaning of this tranformation is to tell the verifier to remove
	//     the Signature from the data prior to canonicalizing. If the Signature is not
	//     contained within the XML fragment that was signed, then the signature was not
	//     enveloped. There would be no need to remove the Signature because the Signature
	//     is not contained in the XML fragment being verified. However.. some brain-dead
	//     verifiyiung systems require this Transform to be present regardless of whether
	//     it makes sense. This behavior will cause Chilkat to add the Transform
	//     regardless.
	void get_Behaviors(CkString &str);
	// A comma-separated list of keywords to specify special behaviors to work around
	// potential oddities or special requirements needed for providing signatures to
	// particular systems. This is an open-ended property where new behaviors can be
	// implemented depending on the needs encountered by Chilkat customers. The
	// possible behaviors are listed below. (At this time, there is only one special
	// behavior.)
	//     ForceAddEnvelopedSignatureTransform The "<Transform
	//     Algorithm="http://www.w3.org/2000/09/xmldsig#enveloped-signature" /> " is
	//     normally only added when the Signature is contained within the XML fragment that
	//     is signed. The meaning of this tranformation is to tell the verifier to remove
	//     the Signature from the data prior to canonicalizing. If the Signature is not
	//     contained within the XML fragment that was signed, then the signature was not
	//     enveloped. There would be no need to remove the Signature because the Signature
	//     is not contained in the XML fragment being verified. However.. some brain-dead
	//     verifiyiung systems require this Transform to be present regardless of whether
	//     it makes sense. This behavior will cause Chilkat to add the Transform
	//     regardless.
	const wchar_t *behaviors(void);
	// A comma-separated list of keywords to specify special behaviors to work around
	// potential oddities or special requirements needed for providing signatures to
	// particular systems. This is an open-ended property where new behaviors can be
	// implemented depending on the needs encountered by Chilkat customers. The
	// possible behaviors are listed below. (At this time, there is only one special
	// behavior.)
	//     ForceAddEnvelopedSignatureTransform The "<Transform
	//     Algorithm="http://www.w3.org/2000/09/xmldsig#enveloped-signature" /> " is
	//     normally only added when the Signature is contained within the XML fragment that
	//     is signed. The meaning of this tranformation is to tell the verifier to remove
	//     the Signature from the data prior to canonicalizing. If the Signature is not
	//     contained within the XML fragment that was signed, then the signature was not
	//     enveloped. There would be no need to remove the Signature because the Signature
	//     is not contained in the XML fragment being verified. However.. some brain-dead
	//     verifiyiung systems require this Transform to be present regardless of whether
	//     it makes sense. This behavior will cause Chilkat to add the Transform
	//     regardless.
	void put_Behaviors(const wchar_t *newVal);

	// Specifies custom XML to be inserted in the KeyInfo element of the Signature. A
	// common use is to provide a wsse:SecurityTokenReference fragment of XML.
	void get_CustomKeyInfoXml(CkString &str);
	// Specifies custom XML to be inserted in the KeyInfo element of the Signature. A
	// common use is to provide a wsse:SecurityTokenReference fragment of XML.
	const wchar_t *customKeyInfoXml(void);
	// Specifies custom XML to be inserted in the KeyInfo element of the Signature. A
	// common use is to provide a wsse:SecurityTokenReference fragment of XML.
	void put_CustomKeyInfoXml(const wchar_t *newVal);

	// The namespace prefix to use for InclusiveNamespaces elements. The default value
	// is "ec". Set this property to the empty string to omit an InclusiveNamespaces
	// prefix. For example, given the default values of IncNamespaceUri and
	// IncNamespacePrefix, generated InclusiveNamespaces elements will appear like
	// this:
	// <ec:InclusiveNamespaces xmlns:ec="http://www.w3.org/2001/10/xml-exc-c14n#"> ... </ec:InclusiveNamespaces>
	void get_IncNamespacePrefix(CkString &str);
	// The namespace prefix to use for InclusiveNamespaces elements. The default value
	// is "ec". Set this property to the empty string to omit an InclusiveNamespaces
	// prefix. For example, given the default values of IncNamespaceUri and
	// IncNamespacePrefix, generated InclusiveNamespaces elements will appear like
	// this:
	// <ec:InclusiveNamespaces xmlns:ec="http://www.w3.org/2001/10/xml-exc-c14n#"> ... </ec:InclusiveNamespaces>
	const wchar_t *incNamespacePrefix(void);
	// The namespace prefix to use for InclusiveNamespaces elements. The default value
	// is "ec". Set this property to the empty string to omit an InclusiveNamespaces
	// prefix. For example, given the default values of IncNamespaceUri and
	// IncNamespacePrefix, generated InclusiveNamespaces elements will appear like
	// this:
	// <ec:InclusiveNamespaces xmlns:ec="http://www.w3.org/2001/10/xml-exc-c14n#"> ... </ec:InclusiveNamespaces>
	void put_IncNamespacePrefix(const wchar_t *newVal);

	// The namespace URI for any InclusiveNamespaces elements that are created. The
	// default value is "http://www.w3.org/2001/10/xml-exc-c14n#". For example, if the
	// IncNamespacePrefix equals "ec" and this property remains at the default value,
	// then the generated Signature element will be:
	// <ec:InclusiveNamespaces xmlns:ec="http://www.w3.org/2001/10/xml-exc-c14n#"> ... </ec:InclusiveNamespaces>
	void get_IncNamespaceUri(CkString &str);
	// The namespace URI for any InclusiveNamespaces elements that are created. The
	// default value is "http://www.w3.org/2001/10/xml-exc-c14n#". For example, if the
	// IncNamespacePrefix equals "ec" and this property remains at the default value,
	// then the generated Signature element will be:
	// <ec:InclusiveNamespaces xmlns:ec="http://www.w3.org/2001/10/xml-exc-c14n#"> ... </ec:InclusiveNamespaces>
	const wchar_t *incNamespaceUri(void);
	// The namespace URI for any InclusiveNamespaces elements that are created. The
	// default value is "http://www.w3.org/2001/10/xml-exc-c14n#". For example, if the
	// IncNamespacePrefix equals "ec" and this property remains at the default value,
	// then the generated Signature element will be:
	// <ec:InclusiveNamespaces xmlns:ec="http://www.w3.org/2001/10/xml-exc-c14n#"> ... </ec:InclusiveNamespaces>
	void put_IncNamespaceUri(const wchar_t *newVal);

	// Specifies the KeyName to be inserted in the KeyInfo element of the Signature if
	// the KeyInfoType equals "KeyName".
	void get_KeyInfoKeyName(CkString &str);
	// Specifies the KeyName to be inserted in the KeyInfo element of the Signature if
	// the KeyInfoType equals "KeyName".
	const wchar_t *keyInfoKeyName(void);
	// Specifies the KeyName to be inserted in the KeyInfo element of the Signature if
	// the KeyInfoType equals "KeyName".
	void put_KeyInfoKeyName(const wchar_t *newVal);

	// Specifies the type of information that will be included in the optional KeyInfo
	// element of the Signature. Possible values are:
	//     None
	//     KeyName
	//     KeyValue
	//     X509Data
	//     Custom
	// 
	// The default value is "KeyValue".
	// 
	// If None, then no KeyInfo element is added to the Signature when generated.
	// 
	// If KeyValue, then the KeyInfo will contain the public key (RSA, DSA, or ECDSA).
	// 
	// If X509Data, then the KeyInfo will contain information about an X.509
	// certificate as specified by the X509Type property.
	// 
	// If Custom, then the KeyInfo will contain the custom XML contained in the
	// CustomKeyInfoXml property.
	// 
	void get_KeyInfoType(CkString &str);
	// Specifies the type of information that will be included in the optional KeyInfo
	// element of the Signature. Possible values are:
	//     None
	//     KeyName
	//     KeyValue
	//     X509Data
	//     Custom
	// 
	// The default value is "KeyValue".
	// 
	// If None, then no KeyInfo element is added to the Signature when generated.
	// 
	// If KeyValue, then the KeyInfo will contain the public key (RSA, DSA, or ECDSA).
	// 
	// If X509Data, then the KeyInfo will contain information about an X.509
	// certificate as specified by the X509Type property.
	// 
	// If Custom, then the KeyInfo will contain the custom XML contained in the
	// CustomKeyInfoXml property.
	// 
	const wchar_t *keyInfoType(void);
	// Specifies the type of information that will be included in the optional KeyInfo
	// element of the Signature. Possible values are:
	//     None
	//     KeyName
	//     KeyValue
	//     X509Data
	//     Custom
	// 
	// The default value is "KeyValue".
	// 
	// If None, then no KeyInfo element is added to the Signature when generated.
	// 
	// If KeyValue, then the KeyInfo will contain the public key (RSA, DSA, or ECDSA).
	// 
	// If X509Data, then the KeyInfo will contain information about an X.509
	// certificate as specified by the X509Type property.
	// 
	// If Custom, then the KeyInfo will contain the custom XML contained in the
	// CustomKeyInfoXml property.
	// 
	void put_KeyInfoType(const wchar_t *newVal);

	// An option Id attribute value for the Signature element. The default value is the
	// empty string, which generates a Signature element with no Id attribute. For
	// example:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#">
	// If this property is set to "abc123", then the Signature element would be
	// generated like this:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#" Id="abc123">
	void get_SigId(CkString &str);
	// An option Id attribute value for the Signature element. The default value is the
	// empty string, which generates a Signature element with no Id attribute. For
	// example:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#">
	// If this property is set to "abc123", then the Signature element would be
	// generated like this:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#" Id="abc123">
	const wchar_t *sigId(void);
	// An option Id attribute value for the Signature element. The default value is the
	// empty string, which generates a Signature element with no Id attribute. For
	// example:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#">
	// If this property is set to "abc123", then the Signature element would be
	// generated like this:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#" Id="abc123">
	void put_SigId(const wchar_t *newVal);

	// Indicates where the Signature is to be located within the XML that is signed.
	// This is a path to the position in the XML where the Signature will be inserted,
	// using Chilkat path syntax (using vertical bar characters to delimit tag names.
	// If the Signature element is to be the root of XML document, then set this
	// property equal to the empty string.
	// 
	// For example, if we have the following SOAP XML and wish to insert the Signature
	// at the indicated location, then the SigLocation property should be set to
	// "SOAP-ENV:Envelope|SOAP-ENV:Header|wsse:Security".
	// <?xml version="1.0" encoding="UTF-8" standalone="no"?>
	// <SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/">
	//     <SOAP-ENV:Header>
	// 	<wsse:Security xmlns:wsse="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd" SOAP-ENV:mustUnderstand="1">
	// 		** The XML Signature is to be inserted here **
	// 	</wsse:Security>
	//     </SOAP-ENV:Header>
	// ...
	// </SOAP-ENV:Envelope>
	// 
	void get_SigLocation(CkString &str);
	// Indicates where the Signature is to be located within the XML that is signed.
	// This is a path to the position in the XML where the Signature will be inserted,
	// using Chilkat path syntax (using vertical bar characters to delimit tag names.
	// If the Signature element is to be the root of XML document, then set this
	// property equal to the empty string.
	// 
	// For example, if we have the following SOAP XML and wish to insert the Signature
	// at the indicated location, then the SigLocation property should be set to
	// "SOAP-ENV:Envelope|SOAP-ENV:Header|wsse:Security".
	// <?xml version="1.0" encoding="UTF-8" standalone="no"?>
	// <SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/">
	//     <SOAP-ENV:Header>
	// 	<wsse:Security xmlns:wsse="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd" SOAP-ENV:mustUnderstand="1">
	// 		** The XML Signature is to be inserted here **
	// 	</wsse:Security>
	//     </SOAP-ENV:Header>
	// ...
	// </SOAP-ENV:Envelope>
	// 
	const wchar_t *sigLocation(void);
	// Indicates where the Signature is to be located within the XML that is signed.
	// This is a path to the position in the XML where the Signature will be inserted,
	// using Chilkat path syntax (using vertical bar characters to delimit tag names.
	// If the Signature element is to be the root of XML document, then set this
	// property equal to the empty string.
	// 
	// For example, if we have the following SOAP XML and wish to insert the Signature
	// at the indicated location, then the SigLocation property should be set to
	// "SOAP-ENV:Envelope|SOAP-ENV:Header|wsse:Security".
	// <?xml version="1.0" encoding="UTF-8" standalone="no"?>
	// <SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/">
	//     <SOAP-ENV:Header>
	// 	<wsse:Security xmlns:wsse="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd" SOAP-ENV:mustUnderstand="1">
	// 		** The XML Signature is to be inserted here **
	// 	</wsse:Security>
	//     </SOAP-ENV:Header>
	// ...
	// </SOAP-ENV:Envelope>
	// 
	void put_SigLocation(const wchar_t *newVal);

	// The namespace prefix of the Signature that is to be created. The default value
	// is "ds". Set this property to the empty string to omit a Signature namespace URI
	// and prefix. For example, given the default values of SigNamespaceUri and
	// SigNamespacePrefix, the generated Signature element will be:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#"> ... </ds:Signature>
	void get_SigNamespacePrefix(CkString &str);
	// The namespace prefix of the Signature that is to be created. The default value
	// is "ds". Set this property to the empty string to omit a Signature namespace URI
	// and prefix. For example, given the default values of SigNamespaceUri and
	// SigNamespacePrefix, the generated Signature element will be:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#"> ... </ds:Signature>
	const wchar_t *sigNamespacePrefix(void);
	// The namespace prefix of the Signature that is to be created. The default value
	// is "ds". Set this property to the empty string to omit a Signature namespace URI
	// and prefix. For example, given the default values of SigNamespaceUri and
	// SigNamespacePrefix, the generated Signature element will be:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#"> ... </ds:Signature>
	void put_SigNamespacePrefix(const wchar_t *newVal);

	// The namespace URI of the Signature that is to be created. The default value is
	// "http://www.w3.org/2000/09/xmldsig#". For example, if the SigNamespacePrefix
	// equals "ds" and this property remains at the default value, then the generated
	// Signature element will be:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#"> ... </ds:Signature>
	void get_SigNamespaceUri(CkString &str);
	// The namespace URI of the Signature that is to be created. The default value is
	// "http://www.w3.org/2000/09/xmldsig#". For example, if the SigNamespacePrefix
	// equals "ds" and this property remains at the default value, then the generated
	// Signature element will be:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#"> ... </ds:Signature>
	const wchar_t *sigNamespaceUri(void);
	// The namespace URI of the Signature that is to be created. The default value is
	// "http://www.w3.org/2000/09/xmldsig#". For example, if the SigNamespacePrefix
	// equals "ds" and this property remains at the default value, then the generated
	// Signature element will be:
	// <ds:Signature xmlns:ds="http://www.w3.org/2000/09/xmldsig#"> ... </ds:Signature>
	void put_SigNamespaceUri(const wchar_t *newVal);

	// The canonicalization method to be used for the SignedInfo when creating the XML
	// signature.
	//     "C14N" -- for Inclusive Canonical XML 1.0 (without comments)
	//     "C14N_11" -- for Inclusive Canonical XML 1.1 (without comments)
	//     "EXCL_C14N" -- for Exclusive Canonical XML (without comments)
	// 
	// The default value is "EXCL_C14N".
	// 
	void get_SignedInfoCanonAlg(CkString &str);
	// The canonicalization method to be used for the SignedInfo when creating the XML
	// signature.
	//     "C14N" -- for Inclusive Canonical XML 1.0 (without comments)
	//     "C14N_11" -- for Inclusive Canonical XML 1.1 (without comments)
	//     "EXCL_C14N" -- for Exclusive Canonical XML (without comments)
	// 
	// The default value is "EXCL_C14N".
	// 
	const wchar_t *signedInfoCanonAlg(void);
	// The canonicalization method to be used for the SignedInfo when creating the XML
	// signature.
	//     "C14N" -- for Inclusive Canonical XML 1.0 (without comments)
	//     "C14N_11" -- for Inclusive Canonical XML 1.1 (without comments)
	//     "EXCL_C14N" -- for Exclusive Canonical XML (without comments)
	// 
	// The default value is "EXCL_C14N".
	// 
	void put_SignedInfoCanonAlg(const wchar_t *newVal);

	// The digest method to be used for signing the SignedInfo part of the Signature.
	// Possible values are "sha1", "sha256", "sha384", and "sha512". The default is
	// "sha256".
	void get_SignedInfoDigestMethod(CkString &str);
	// The digest method to be used for signing the SignedInfo part of the Signature.
	// Possible values are "sha1", "sha256", "sha384", and "sha512". The default is
	// "sha256".
	const wchar_t *signedInfoDigestMethod(void);
	// The digest method to be used for signing the SignedInfo part of the Signature.
	// Possible values are "sha1", "sha256", "sha384", and "sha512". The default is
	// "sha256".
	void put_SignedInfoDigestMethod(const wchar_t *newVal);

	// The inclusive namespace prefix list to be added, if any, when the
	// SignedInfoCanonAlg is equal to "EXCL_C14N". The defautl value is the empty
	// string. If namespaces are listed, they are separated by space characters.
	// 
	// If, for example, this property is set to "wsse SOAP-ENV", then the
	// CanonicalizationMethod part of the SignedInfo that is generated would look like
	// this:
	// <ds:SignedInfo>
	//     <ds:CanonicalizationMethod Algorithm="http://www.w3.org/2001/10/xml-exc-c14n#">
	//       <InclusiveNamespaces xmlns="http://www.w3.org/2001/10/xml-exc-c14n#" PrefixList="wsse SOAP-ENV" />
	//     </ds:CanonicalizationMethod>
	// ...
	// </ds:SignedInfo>
	// 
	void get_SignedInfoPrefixList(CkString &str);
	// The inclusive namespace prefix list to be added, if any, when the
	// SignedInfoCanonAlg is equal to "EXCL_C14N". The defautl value is the empty
	// string. If namespaces are listed, they are separated by space characters.
	// 
	// If, for example, this property is set to "wsse SOAP-ENV", then the
	// CanonicalizationMethod part of the SignedInfo that is generated would look like
	// this:
	// <ds:SignedInfo>
	//     <ds:CanonicalizationMethod Algorithm="http://www.w3.org/2001/10/xml-exc-c14n#">
	//       <InclusiveNamespaces xmlns="http://www.w3.org/2001/10/xml-exc-c14n#" PrefixList="wsse SOAP-ENV" />
	//     </ds:CanonicalizationMethod>
	// ...
	// </ds:SignedInfo>
	// 
	const wchar_t *signedInfoPrefixList(void);
	// The inclusive namespace prefix list to be added, if any, when the
	// SignedInfoCanonAlg is equal to "EXCL_C14N". The defautl value is the empty
	// string. If namespaces are listed, they are separated by space characters.
	// 
	// If, for example, this property is set to "wsse SOAP-ENV", then the
	// CanonicalizationMethod part of the SignedInfo that is generated would look like
	// this:
	// <ds:SignedInfo>
	//     <ds:CanonicalizationMethod Algorithm="http://www.w3.org/2001/10/xml-exc-c14n#">
	//       <InclusiveNamespaces xmlns="http://www.w3.org/2001/10/xml-exc-c14n#" PrefixList="wsse SOAP-ENV" />
	//     </ds:CanonicalizationMethod>
	// ...
	// </ds:SignedInfo>
	// 
	void put_SignedInfoPrefixList(const wchar_t *newVal);

	// Selects the signature algorithm to be used when using an RSA key to sign. The
	// default value is "PKCS1-v1_5". This can be set to "RSASSA-PSS" (or simply "pss")
	// to use the RSASSA-PSS signature scheme.
	// 
	// Note: This property only applies when signing with an RSA private key. It does
	// not apply for ECC or DSA private keys.
	// 
	void get_SigningAlg(CkString &str);
	// Selects the signature algorithm to be used when using an RSA key to sign. The
	// default value is "PKCS1-v1_5". This can be set to "RSASSA-PSS" (or simply "pss")
	// to use the RSASSA-PSS signature scheme.
	// 
	// Note: This property only applies when signing with an RSA private key. It does
	// not apply for ECC or DSA private keys.
	// 
	const wchar_t *signingAlg(void);
	// Selects the signature algorithm to be used when using an RSA key to sign. The
	// default value is "PKCS1-v1_5". This can be set to "RSASSA-PSS" (or simply "pss")
	// to use the RSASSA-PSS signature scheme.
	// 
	// Note: This property only applies when signing with an RSA private key. It does
	// not apply for ECC or DSA private keys.
	// 
	void put_SigningAlg(const wchar_t *newVal);

	// Specifies the kind of X.509 certificate information is provided in the KeyInfo
	// element when the KeyInfoType equals "X509Data". Possible values are:
	//     Certificate
	//     CertChain
	//     IssuerSerial
	//     SubjectName
	//     SKI
	// 
	// The default value is "Certificate".
	// 
	// If Certificate, then the KeyInfo will contain the base64 encoded X.509v3
	// certificate.
	// 
	// If CertChain, then the KeyInfo will contain the base64 encoded X.509v3
	// certificate as well as any certificates available in the chain of authentication
	// to the root cert.
	// 
	// If IssuerSerial, then the KeyInfo will contain the X.509 issuer's distinguished
	// name and the signing certificate's serial number.
	// 
	// If SubjectName, then the KeyInfo will contain the X.509 subject distinguished
	// name.
	// 
	// If SKI, then the KeyInfo will contain the base64 encoded value of the cert's
	// X.509 SubjectKeyIdentifier extension.
	// 
	void get_X509Type(CkString &str);
	// Specifies the kind of X.509 certificate information is provided in the KeyInfo
	// element when the KeyInfoType equals "X509Data". Possible values are:
	//     Certificate
	//     CertChain
	//     IssuerSerial
	//     SubjectName
	//     SKI
	// 
	// The default value is "Certificate".
	// 
	// If Certificate, then the KeyInfo will contain the base64 encoded X.509v3
	// certificate.
	// 
	// If CertChain, then the KeyInfo will contain the base64 encoded X.509v3
	// certificate as well as any certificates available in the chain of authentication
	// to the root cert.
	// 
	// If IssuerSerial, then the KeyInfo will contain the X.509 issuer's distinguished
	// name and the signing certificate's serial number.
	// 
	// If SubjectName, then the KeyInfo will contain the X.509 subject distinguished
	// name.
	// 
	// If SKI, then the KeyInfo will contain the base64 encoded value of the cert's
	// X.509 SubjectKeyIdentifier extension.
	// 
	const wchar_t *x509Type(void);
	// Specifies the kind of X.509 certificate information is provided in the KeyInfo
	// element when the KeyInfoType equals "X509Data". Possible values are:
	//     Certificate
	//     CertChain
	//     IssuerSerial
	//     SubjectName
	//     SKI
	// 
	// The default value is "Certificate".
	// 
	// If Certificate, then the KeyInfo will contain the base64 encoded X.509v3
	// certificate.
	// 
	// If CertChain, then the KeyInfo will contain the base64 encoded X.509v3
	// certificate as well as any certificates available in the chain of authentication
	// to the root cert.
	// 
	// If IssuerSerial, then the KeyInfo will contain the X.509 issuer's distinguished
	// name and the signing certificate's serial number.
	// 
	// If SubjectName, then the KeyInfo will contain the X.509 subject distinguished
	// name.
	// 
	// If SKI, then the KeyInfo will contain the base64 encoded value of the cert's
	// X.509 SubjectKeyIdentifier extension.
	// 
	void put_X509Type(const wchar_t *newVal);



	// ----------------------
	// Methods
	// ----------------------
	// Specifies an enveloped Reference to be added to the Signature when generated. An
	// enveloped Reference is for data contained within the Signature. (The Signature
	// is to be an enveloping signature, and the data is enveloped by the Signature.)
	// 
	// The id is the value of the Id attribute of the Object element that is to be
	// contained within the generated Signature. The content is the text content to be
	// contained in the Object. Binary data can be signed by passing the bytes in content
	// in an encoded format (such as base64 or hex).
	// 
	// The digestMethod is the digest method and can be one of the following: "sha1", "sha256",
	// "sha384", "sha512", "ripemd160", or "md5".
	// 
	// The canonMethod is the canonicalization method, and can be one of the following:
	//     "C14N" -- for Inclusive Canonical XML (without comments)
	//     "C14N_11" -- for Inclusive Canonical XML 1.1 (without comments)
	//     "EXCL_C14N" -- for Exclusive Canonical XML (without comments)
	// 
	// The refType is optional and is usually not needed. Set this to the empty string
	// unless it is desired to add a Type attribute to the Reference that is advisory
	// only.
	// 
	bool AddEnvelopedRef(const wchar_t *id, CkStringBuilderW &content, const wchar_t *digestMethod, const wchar_t *canonMethod, const wchar_t *refType);

	// Specifies an external non-XML binary data Reference to be added to the Signature
	// when generated.
	// 
	// The uri is the value of the URI attribute of the Reference.
	// 
	// The content contains the binary data to be digested according to the digestMethod.
	// 
	// The digestMethod is the digest method and can be one of the following: "sha1", "sha256",
	// "sha384", "sha512", "ripemd160", or "md5".
	// 
	// The refType is optional and is usually not needed. Set this to the empty string
	// unless it is desired to add a Type attribute to the Reference that is advisory
	// only.
	// 
	bool AddExternalBinaryRef(const wchar_t *uri, CkBinDataW &content, const wchar_t *digestMethod, const wchar_t *refType);

	// Specifies an external file Reference to be added to the Signature when
	// generated.
	// 
	// The uri is the value of the URI attribute of the Reference. It can (and likely
	// will) be different than the localFilePath which is the path to the local file to be
	// added. (The local file is not read until the XML digital signature is actually
	// created.)
	// 
	// The digestMethod is the digest method and can be one of the following: "sha1", "sha256",
	// "sha384", "sha512", "ripemd160", or "md5".
	// 
	// The refType is optional and is usually not needed. Set this to the empty string
	// unless it is desired to add a Type attribute to the Reference that is advisory
	// only.
	// 
	bool AddExternalFileRef(const wchar_t *uri, const wchar_t *localFilePath, const wchar_t *digestMethod, const wchar_t *refType);

	// Specifies an external non-XML text data Reference to be added to the Signature
	// when generated.
	// 
	// The uri is the value of the URI attribute of the Reference.
	// 
	// The content contains the non-XML data to be digested according to the charset. The
	// charset specifies the charset (such as "utf-8", "windows-1252", etc.) for the byte
	// reprsentation of the text to be digested. The includeBom indicates whether the BOM
	// (Byte Order Mark, also known as the preamble) is included in the byte
	// representation that is digested.
	// 
	// The digestMethod is the digest method and can be one of the following: "sha1", "sha256",
	// "sha384", "sha512", "ripemd160", or "md5".
	// 
	// The refType is optional and is usually not needed. Set this to the empty string
	// unless it is desired to add a Type attribute to the Reference that is advisory
	// only.
	// 
	bool AddExternalTextRef(const wchar_t *uri, CkStringBuilderW &content, const wchar_t *charset, bool includeBom, const wchar_t *digestMethod, const wchar_t *refType);

	// Specifies an external XML Reference to be added to the Signature when generated.
	// 
	// The uri is the value of the URI attribute of the Reference.
	// 
	// The content contains the XML document to be referenced.
	// 
	// The digestMethod is the digest method and can be one of the following: "sha1", "sha256",
	// "sha384", "sha512", "ripemd160", or "md5".
	// 
	// The canonMethod is the canonicalization method, and can be one of the following.
	//     "C14N" -- for Inclusive Canonical XML (without comments)
	//     "C14N_11" -- for Inclusive Canonical XML 1.1 (without comments)
	//     "EXCL_C14N" -- for Exclusive Canonical XML (without comments)
	// 
	// The refType is optional and is usually not needed. Set this to the empty string
	// unless it is desired to add a Type attribute to the Reference that is advisory
	// only.
	// 
	bool AddExternalXmlRef(const wchar_t *uri, CkStringBuilderW &content, const wchar_t *digestMethod, const wchar_t *canonMethod, const wchar_t *refType);

	// Specifies a same document Reference to be added to the Signature when generated.
	// An same document Reference can be the entire XML document, or a fragment of the
	// XML document.
	// 
	// The id can be the empty string to sign the entire XML document, or it can be
	// the fragment identifier to sign a portion of the XML document.
	// 
	// The digestMethod is the digest method and can be one of the following: "sha1", "sha256",
	// "sha384", "sha512", "ripemd160", or "md5".
	// 
	// The canonMethod is the canonicalization method, and can be one of the following:
	//     "C14N" -- for Inclusive Canonical XML (without comments)
	//     "C14N_11" -- for Inclusive Canonical XML 1.1 (without comments)
	//     "EXCL_C14N" -- for Exclusive Canonical XML (without comments)
	// 
	// If exclusive canonicalization is selected, then the prefixList can contain a space
	// separated list of inclusive namespace prefixes. For inclusive canonicalization,
	// this argument is ignored. In general, pass an empty string for this argument
	// unless you have specific knowledge of namespace prefixes that need to be treated
	// as inclusive when EXCL_C14N is used.
	// 
	// Starting in Chilkat v9.5.0.70, the prefixList can be set to the keyword "_EMPTY_" to
	// force the generation of an empty PrefixList under the Transform. For example:
	//   <ds:Transform Algorithm="http://www.w3.org/2001/10/xml-exc-c14n#">
	// 	<ec:InclusiveNamespaces xmlns:ec="http://www.w3.org/2001/10/xml-exc-c14n#" PrefixList=""/>
	//   </ds:Transform>
	// 
	// The refType is optional and is usually not needed. Set this to the empty string
	// unless it is desired to add a Type attribute to the Reference that is advisory
	// only.
	// 
	bool AddSameDocRef(const wchar_t *id, const wchar_t *digestMethod, const wchar_t *canonMethod, const wchar_t *prefixList, const wchar_t *refType);

	// Creates an XML Digital Signature. The application passes in the XML to be
	// signed, and the signed XML is returned. If creating an enveloping signature
	// where the Signature element is the root, then the inXml may be the empty string.
	bool CreateXmlDSig(const wchar_t *inXml, CkString &outStr);
	// Creates an XML Digital Signature. The application passes in the XML to be
	// signed, and the signed XML is returned. If creating an enveloping signature
	// where the Signature element is the root, then the inXml may be the empty string.
	const wchar_t *createXmlDSig(const wchar_t *inXml);

	// Creates an XML Digital Signature. The application passes the XML to be signed in
	// sbXml, and it is replaced with the signed XML if successful. (Thus, sbXml is both
	// an input and output argument.) Note: If creating an enveloping signature where
	// the Signature element is to be the root element, then the passed-in sbXml may be
	// empty.
	bool CreateXmlDSigSb(CkStringBuilderW &sbXml);

	// Sets the HMAC key to be used if the Signature is to use an HMAC signing
	// algorithm. The encoding specifies the encoding of key, and can be "hex", "base64",
	// "ascii", or any of the binary encodings supported by Chilkat in the link below.
	bool SetHmacKey(const wchar_t *key, const wchar_t *encoding);

	// Sets the private key to be used for creating the XML signature. The private key
	// may be an RSA key, a DSA key, or an ECDSA key.
	bool SetPrivateKey(CkPrivateKeyW &privKey);

	// Specifies the X.509 certificate to be used for the KeyInfo element when the
	// KeyInfoType equals "X509Data". If usePrivateKey is true, then the private key will also
	// be set using the certificate's private key. Thus, the SetPrivateKey method does
	// not need to be called. If usePrivateKey is true, and the certificate does not have an
	// associated private key available, then this method will return false.
	// 
	// Note: A certificate's private key is not stored within a certificate itself. If
	// the certificate (cert) was obtained from a PFX, Java KeyStore, or other such
	// source, which are containers for both certs and private keys, then Chilkat would
	// have associated the cert with the private key when loading the PFX or JKS, and
	// all is good. The same holds true if, on a Windows system, the certificate was
	// obtained from a Windows-based registry certificate store where the private key
	// was installed with the permission to export.
	// 
	// If, however, the certificate was loaded from a .cer file, or another type of
	// file that contains only the certificate and not the private key, then the
	// associated private key needs to be obtained by the application and provided by
	// calling SetPrivateKey.
	// 
	bool SetX509Cert(CkCertW &cert, bool usePrivateKey);





	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
